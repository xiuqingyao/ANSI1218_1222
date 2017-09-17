//--------------------------------- include files -------------------------------------------------------//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "ansi_c1218.h"
#include "ansi_tblmgr.h"

//--------------------------------- variable declare ---------------------------------------------------------//
static stPsemInfo g_stPsemFrameInfo;
static stPsemInfo g_stLastPsemFrameInfo;
static eC1218SessionStatus g_eSessionStatus = E_C1218_STATE_SESSION;//E_C1218_STATE_BASE;
static stNegotiateService g_stNegService;

//--------------------------------- function declare ---------------------------------------------------------//
/**
 * init global variable
 *
 * @param pData: received c12.18 data
 */
void InitC1218PsemInfo(void)
{
    memset(&g_stPsemFrameInfo, 0x00, sizeof(g_stPsemFrameInfo));
}

/**
 * check PSEM frame validity
 *
 * @param headerSize: received c12.18 frame header size
 * @param pData: received c12.18 frame
 */
void SaveC1218FrameInfo(uint8 headerSize, uint8 *pData)
{
    memset(&g_stPsemFrameInfo, 0x00, sizeof(g_stPsemFrameInfo));

    /*skip tag 'EE'*/
    pData++;

    /*save current frame info*/
    g_stPsemFrameInfo.headerSize = headerSize;
    g_stPsemFrameInfo.deviceId = *pData++;
    g_stPsemFrameInfo.ctlByte.byte = *pData++;
    g_stPsemFrameInfo.frameCnt = *pData++;
#if (LITTLE_ENDIAN == 1)
    g_stPsemFrameInfo.dataLen.b[1] = *pData++;//data length
    g_stPsemFrameInfo.dataLen.b[0] = *pData++;
#else
    g_stPsemFrameInfo.dataLen.b[0] = *pData++;//data length
    g_stPsemFrameInfo.dataLen.b[1] = *pData++;
#endif
    pData += g_stPsemFrameInfo.dataLen.w;
#if (LITTLE_ENDIAN == 1)
    g_stPsemFrameInfo.frameCrcVal.b[1] = *pData++;//data length
    g_stPsemFrameInfo.frameCrcVal.b[0] = *pData++;
#else
    g_stPsemFrameInfo.frameCrcVal.b[0] = *pData++;//data length
    g_stPsemFrameInfo.frameCrcVal.b[1] = *pData++;
#endif
}

/**
 * check PSEM frame validity
 *
 * @param pReqFrame: received c12.18 frame
 */
uint8 CheckC1218FrameValidity(uint8 *pReqFrame)
{
    uint8 retVal = 1;
    uint16 crcTemp = 0;
    uint16 dataLen = g_stPsemFrameInfo.headerSize + g_stPsemFrameInfo.dataLen.w;

    /*check duplicate frame*/
    /*if identity, toggle bit and valid CRC are the same as previous frame,*/
    /*current frame is the duplicated one*/
    if ((g_stLastPsemFrameInfo.deviceId == g_stPsemFrameInfo.deviceId) &&
        (g_stLastPsemFrameInfo.ctlByte.bits.TOGGLE_FLAG == g_stPsemFrameInfo.ctlByte.bits.TOGGLE_FLAG) &&
        (g_stLastPsemFrameInfo.frameCrcVal.w == g_stPsemFrameInfo.frameCrcVal.w))
    {
        retVal = 0;
    }

    /*check CRC value*/
    crcTemp = crc(dataLen, pReqFrame);
    if (g_stPsemFrameInfo.frameCrcVal.w != crcTemp)
    {
        retVal = 0;
    }

    return retVal;
}

/**
 * parse PSEM frame
 *
 * @param pData: received c12.18 frame
 */
uint8 *ParseC1218PsemFrame(uint8 *pReqFrame)
{
    uint8 *pRet  = NULL;
    uint8 *pData = (uint8 *)pReqFrame;
    uint8 headerSize = C1218_REQ_HEADER_SIZE;

    /*check status of current session*/
    if ((g_eSessionStatus == E_C1218_STATE_ID) || (g_eSessionStatus == E_C1218_STATE_SESSION))
    {
        pData += 1;//skip response tag '06'
    }

    /*save current frame info*/
    SaveC1218FrameInfo(headerSize, pData);

    /*check frame validity from beginning of the frame*/
    if (CheckC1218FrameValidity(pData))
    {
        /*return request payload*/
        pRet = pData + g_stPsemFrameInfo.headerSize;
    }

    return pRet;
}

/**
 * build ERROR frame
 *
 * @param pRespData: response c12.18 data
 */
void BuildC1218NACKResp(uint8 *pRespData)
{
    uint8 *pData = (uint8 *)pRespData;
    uint16 crcVal = 0;
    uint16 errCode = CODE_ERR;

    pData[0] = CODE_C1218_NAK;
    pData[1] = CODE_C1218_STP;
    pData[2] = g_stPsemFrameInfo.deviceId;
    pData[3] = g_stPsemFrameInfo.ctlByte.byte;
    pData[4] = g_stPsemFrameInfo.frameCnt;
#if (LITTLE_ENDIAN == 1)
    pData[5] = (errCode >> 8) & 0xFF;//data length
    pData[6] = errCode & 0xFF;
#else
    pData[5] = errCode & 0xFF;//data length
    pData[6] = (errCode >> 8) & 0xFF;
#endif
    pData[7] = CODE_ERR;

    crcVal = crc(C1218_RESP_HEADER_SIZE, pRespData + 1);
#if 0
#if (LITTLE_ENDIAN == 1)
    crcVal.b[1] = *pData++;//data length
    crcVal.b[0] = *pData++;
#else
    crcVal.b[0] = *pData++;//data length
    crcVal.b[1] = *pData++;
#endif
#endif
    memcpy(pRespData + C1218_RESP_HEADER_SIZE + 1, &crcVal, sizeof(uint16));

    /*clear information*/
    memset(&g_stPsemFrameInfo, 0x00, sizeof(g_stPsemFrameInfo));
}

/**
 * build C12.22 response frame
 *
 * @param type: resp type
 * @param serviceCode: service code
 * @param pRespData: output response data
 */
void BuildC1218Resp(uint8 *pReqData, uint8 *pRespData)
{
    stPsemPayload stPsemData;
	memset(&stPsemData, 0x00, sizeof(stPsemPayload));
    stPsemData.pData = pRespData + C1218_RESP_HEADER_SIZE;

    /*build PSEM payload*/
	BuildC1218Payload(pReqData, &stPsemData);

	/*build PSEM frame*/
	BuildC1218PsemFrame(&stPsemData, pRespData);

	/*save current PSEM frame info*/
	memset(&g_stLastPsemFrameInfo, 0x00, sizeof(g_stLastPsemFrameInfo));
	memcpy(&g_stLastPsemFrameInfo, &g_stPsemFrameInfo, sizeof(g_stPsemFrameInfo));
}

/**
 * build PSEM frame
 *
 * @param pData: received c12.18 data
 */
void BuildC1218PsemFrame(stPsemPayload *pPayload, uint8 *pRespData)
{
    uint16 crcVal = 0;

    /*add header to frame*/
    pRespData[0] = g_stPsemFrameInfo.ackType;
    pRespData[1] = CODE_C1218_STP;
    pRespData[2] = g_stPsemFrameInfo.deviceId;
    pRespData[3] = g_stPsemFrameInfo.ctlByte.byte;
    pRespData[4] = g_stPsemFrameInfo.frameCnt;
#if (LITTLE_ENDIAN == 1)
    pRespData[5] = (pPayload->nSize >> 8) & 0xFF;
    pRespData[6] = (pPayload->nSize) & 0xFF;
#else
    pRespData[5] = (pPayload->nSize) & 0xFF;
    pRespData[6] = (pPayload->nSize >> 8) & 0xFF;
#endif
    //memcpy(&pRespData[5], &pPayload->nSize, sizeof(uint16));

    /*calculate CRC-16 value*/
    crcVal = crc(pPayload->nSize + C1218_RESP_HEADER_SIZE - 1, pRespData + 1);
#if (LITTLE_ENDIAN == 1)
    uint8 *pData = NULL;
    pData = pRespData + C1218_RESP_HEADER_SIZE + pPayload->nSize;
    pData[0] = (crcVal >> 8) & 0xFF;
    pData[1] = (crcVal) & 0xFF;
#else
    memcpy(pRespData + C1218_RESP_HEADER_SIZE + pPayload->nSize, &crcVal, sizeof(uint16));
#endif
}

/**
 * build PSEM payload
 *
 * @param type: resp type
 * @param serviceCode: service code
 * @param pPsemData: PSEM response data
 */
void BuildC1218Payload(uint8 *pReqData, stPsemPayload *pPsemData)
{
    g_stPsemFrameInfo.ackType = CODE_C1218_ACK;
    uint8 serviceCode = *pReqData++;

    switch (serviceCode)
    {
        case CODE_IDENTIFICATION://Identification
            {
                /*identification service only processed in IDLE status*/
                if (g_eSessionStatus != E_C1218_STATE_BASE)
                {
                    g_stPsemFrameInfo.ackType = CODE_C1218_NAK;

                    pPsemData->pData[0] = CODE_ISSS;
                    pPsemData->nSize++;

                    return;
                }
                else
                {
                    pPsemData->pData[0] = CODE_OK;
                    pPsemData->nSize++;
                    pPsemData->pData[1] = CODE_C1218_STD;
                    pPsemData->nSize++;
                    pPsemData->pData[2] = CODE_C1218_VER;
                    pPsemData->nSize++;
                    pPsemData->pData[3] = CODE_REV;
                    pPsemData->nSize++;
                    pPsemData->pData[4] = CODE_FEATURE;
                    pPsemData->nSize++;

                    /*change session status to IDENTIFICATION*/
                    g_eSessionStatus = E_C1218_STATE_ID;
                }
            }
            break;
        case CODE_NEGOTIATE60:		//baud rate not change, use default baud rate
        case CODE_NEGOTIATE61:		//300
        case CODE_NEGOTIATE62:		//600
        case CODE_NEGOTIATE63:		//1200
        case CODE_NEGOTIATE64:		//2400
        case CODE_NEGOTIATE65:		//4800
        case CODE_NEGOTIATE66:		//9600
        case CODE_NEGOTIATE67:		//14400
        case CODE_NEGOTIATE68:		//19200
        case CODE_NEGOTIATE69:		//28800
        case CODE_NEGOTIATE6A:		//57600
        case CODE_NEGOTIATE6B:		//38400
            {
                /*negotiate service only processed in IDENTIFICATION status*/
                if (g_eSessionStatus != E_C1218_STATE_ID)
                {
                    g_stPsemFrameInfo.ackType = CODE_C1218_NAK;

                    pPsemData->pData[0] = CODE_ISSS;
                    pPsemData->nSize++;

                    return;
                }
                else
                {
                    /*save negotiate info*/
                    memset(&g_stNegService, 0x00, sizeof(stNegotiateService));
        #if (LITTLE_ENDIAN == 1)
                    g_stNegService.nMaxBytes.b[1] = *pReqData++;//packet-size
                    g_stNegService.nMaxBytes.b[0] = *pReqData++;
        #else
                    g_stNegService.nMaxBytes.b[0] = *pReqData++;//packet-size
                    g_stNegService.nMaxBytes.b[1] = *pReqData++;
        #endif
                    g_stNegService.nMaxFrames = *pReqData++;
                    g_stNegService.nBaudrate = *pReqData++;

                    /*fill payload*/
                    pPsemData->pData[0] = CODE_OK;
                    pPsemData->nSize++;
        #if (LITTLE_ENDIAN == 1)
                    pPsemData->pData[1] = (MAX_BYTES_PER_FRAME >> 8) & 0xFF;
                    pPsemData->pData[2] = (MAX_BYTES_PER_FRAME) & 0xFF;
                    pPsemData->nSize += 2;
        #else
                    pPsemData->pData[1] = (MAX_BYTES_PER_FRAME) & 0xFF;
                    pPsemData->pData[2] = (MAX_BYTES_PER_FRAME >> 8) & 0xFF;
                    pPsemData->nSize += 2;
        #endif
                    pPsemData->pData[3] = g_stNegService.nMaxFrames;
                    pPsemData->nSize++;
                    pPsemData->pData[4] = g_stNegService.nBaudrate;
                    pPsemData->nSize++;
                }
            }
            break;
        case CODE_LOGON://logon
            {
                /*log on service only processed in IDENTIFICATION status*/
                if (g_eSessionStatus != E_C1218_STATE_ID)
                {
                    g_stPsemFrameInfo.ackType = CODE_C1218_NAK;

                    pPsemData->pData[0] = CODE_ISSS;
                    pPsemData->nSize++;

                    return;
                }
                else
                {
                    pPsemData->pData[0] = CODE_OK;
                    pPsemData->nSize++;

                    /*change session status to SESSION*/
                    g_eSessionStatus = E_C1218_STATE_SESSION;
                }
            }
            break;
        case CODE_READ30://full read
        case CODE_READ3F://partial read
            {
                /*security service only processed in SESSION status*/
                if (g_eSessionStatus != E_C1218_STATE_SESSION)
                {
                    g_stPsemFrameInfo.ackType = CODE_C1218_NAK;

                    pPsemData->pData[0] = CODE_ISSS;
                    pPsemData->nSize++;

                    return;
                }

                u8_16_t tableid;
                u8_32_t offset;
                u8_16_t count;
                uint8 retCode = CODE_OK;

#if (LITTLE_ENDIAN == 1)
                tableid.b[1] = *pReqData++;//table id
                tableid.b[0] = *pReqData++;
#else
                tableid.b[0] = *pReqData++;//table id
                tableid.b[1] = *pReqData++;
#endif

                if (CODE_READ3F == serviceCode)
                {

#if (LITTLE_ENDIAN == 1)
                    offset.b[3] = 0x00;//offset
                    offset.b[2] = *pReqData++;
                    offset.b[1] = *pReqData++;
                    offset.b[0] = *pReqData++;
                    count.b[1] = *pReqData++;//read bytes
                    count.b[0] = *pReqData++;
#else
                    offset.b[0] = 0x00;//offset
                    offset.b[1] = *pReqData++;
                    offset.b[2] = *pReqData++;
                    offset.b[3] = *pReqData++;
                    count.b[0] = *pReqData++;//read bytes
                    count.b[1] = *pReqData++;
#endif // LITTLE_ENDIAN

                }
                else
                {
                    offset.l = 0;
                    count.w = 0x0000;
                }

                retCode = PartialRead(serviceCode, tableid.w, offset.l, count.w, pPsemData->pData, &pPsemData->nSize, &pPsemData->chkSum);
                if (CODE_OK == retCode)
                {
                    count.w = pPsemData->nSize;

                    pPsemData->pData[0] = retCode;
#if (LITTLE_ENDIAN == 1)
                    pPsemData->pData[1] = count.b[1];
                    pPsemData->pData[2] = count.b[0];
#else
                    pPsemData->pData[1] = count.b[0];
                    pPsemData->pData[2] = count.b[1];
#endif
                    pPsemData->nSize += 3;
                    pPsemData->pData[pPsemData->nSize] = GetChecksum(pPsemData->chkSum);
                    pPsemData->nSize++;
                }
                else
                {
                    memset(&pPsemData->pData[0], 0x00, pPsemData->nSize);//need to change
                    pPsemData->pData[0] = retCode;
                    pPsemData->nSize = 1;
                }
            }
            break;
        case CODE_WRITE40://full write
        case CODE_WRITE4F://partial write
            {
                /*security service only processed in SESSION status*/
                if (g_eSessionStatus != E_C1218_STATE_SESSION)
                {
                    g_stPsemFrameInfo.ackType = CODE_C1218_NAK;

                    pPsemData->pData[0] = CODE_ISSS;
                    pPsemData->nSize++;

                    return;
                }

                u8_16_t tableid;
                u8_32_t offset;
                u8_16_t count;
                //uint8 retCode = CODE_OK;

#if (LITTLE_ENDIAN == 1)
                tableid.b[1] = *pReqData++;//table id
                tableid.b[0] = *pReqData++;
#else
                tableid.b[0] = *pReqData++;//table id
                tableid.b[1] = *pReqData++;
#endif

                if (CODE_WRITE4F == serviceCode)
                {
#if (LITTLE_ENDIAN == 1)
                    offset.b[3] = 0x00;       //offset
                    offset.b[2] = *pReqData++;
                    offset.b[1] = *pReqData++;
                    offset.b[0] = *pReqData++;
                    count.b[1] = *pReqData++;  //count
                    count.b[0] = *pReqData++;
#else
                    offset.b[0] = 0x00;//offset
                    offset.b[1] = *pReqData++;
                    offset.b[2] = *pReqData++;
                    offset.b[3] = *pReqData++;
                    count.b[0] = *pReqData++;//read bytes
                    count.b[1] = *pReqData++;
#endif // LITTLE_ENDIAN

                }
                else
                {
                    offset.l = 0;
#if (LITTLE_ENDIAN == 1)
                    count.b[1] = *pReqData++;  //count
                    count.b[0] = *pReqData++;
#else
                    count.b[0] = *pReqData++;//read bytes
                    count.b[1] = *pReqData++;
#endif // LITTLE_ENDIAN
                }

                pPsemData->pData[0] = PartialWrite(serviceCode, tableid.w, offset.l, count.w, pReqData);
                pPsemData->nSize++;
            }
            break;
        case CODE_SECURITY://security
            {
                /*security service only processed in SESSION status*/
                if (g_eSessionStatus != E_C1218_STATE_SESSION)
                {
                    g_stPsemFrameInfo.ackType = CODE_C1218_NAK;

                    pPsemData->pData[0] = CODE_ISSS;
                    pPsemData->nSize++;

                    return;
                }
                else
                {
                    pPsemData->pData[0] = CODE_OK;
                    pPsemData->nSize++;
                }
            }
            break;
        case CODE_WAIT://wait
            {
                pPsemData->pData[0] = CODE_OK;
                pPsemData->nSize++;
            }
            break;
        case CODE_LOGOFF://log off
            {
                /*security service only processed in SESSION status*/
                if (g_eSessionStatus != E_C1218_STATE_SESSION)
                {
                    g_stPsemFrameInfo.ackType = CODE_C1218_NAK;

                    pPsemData->pData[0] = CODE_ISSS;
                    pPsemData->nSize++;

                    return;
                }
                else
                {
                    pPsemData->pData[0] = CODE_OK;
                    pPsemData->nSize++;

                    /*change session status return to IDENTIFICATION*/
                    g_eSessionStatus = E_C1218_STATE_ID;
                }
            }
            break;
        case CODE_TERMINATE://terminate
            {
                pPsemData->pData[0] = CODE_OK;
                pPsemData->nSize++;

                /*close session, return status to IDLE*/
                g_eSessionStatus = E_C1218_STATE_BASE;
            }
            break;
        default:
            {
                g_stPsemFrameInfo.ackType = CODE_C1218_NAK;

                pPsemData->pData[0] = CODE_SNS;
                pPsemData->nSize++;
            }
            break;
    }
}

//==================================================================================
#if (SW_SIMULATION == 1)
uint8 TestC1218SingleFrame(uint8 *test_data)
{
    uint8 *pPsemData = NULL;
    uint16 cnt = 0;
    uint8 pRespData[1024] = {0};

    InitC1218PsemInfo();
    pPsemData = ParseC1218PsemFrame(test_data);
    if (pPsemData != 0)
    {
        BuildC1218Resp(pPsemData, pRespData);
    }
    else
    {
        BuildC1218NACKResp(pRespData);
    }

    //print test result when response bit(0~1) is 0
    printf("\r\nrequest data:===================\r\n");
    for (; cnt < 50; cnt++)
    {
        printf ("0x%02x ", test_data[cnt]);
        if ((cnt+1)%10 == 0)
            printf("\r\n");
    }
    printf("\r\n");

    printf("\r\nresponse data:==================\r\n");
    for (cnt = 0; cnt < 50; cnt++)
    {
        printf ("0x%02x ", pRespData[cnt]);
        if ((cnt+1)%10 == 0)
            printf("\r\n");
    }
    printf("\r\n");

    return 1;
}
#endif
