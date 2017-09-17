#ifndef ANSI_C_1218_H
#define ANSI_C_1218_H

#include "typedef.h"
#include "ansi_def.h"
#include "crc.h"

#define C1218_TAG_SIZE              (sizeof(uint8))
#define C1218_REQ_HEADER_SIZE       (6)
#define C1218_RESP_HEADER_SIZE      (7)//ACK + response data header
//#define PSEM_PAYLOAD_SIZE         (64)

/*ACK type*/
#define CODE_C1218_ACK			    0x06
#define CODE_C1218_NAK			    0x15

/*header field*/
#define CODE_C1218_STP			    0xEE
#define CODE_C1218_IDENTITY		    0x00

/*value in identification response*/
#define CODE_C1218_STD			    0x00
#define CODE_C1218_VER			    0x01

/*default setting*/
#define MAX_BYTES_PER_FRAME         0x0040 //package size, 64bytes
#define MAX_NUM_FRAMES              0x01   //number of packets

typedef enum
{
    E_C1218_STATE_BASE,
    E_C1218_STATE_ID,
    E_C1218_STATE_SESSION,
    E_C1218_STATE_NONE,
} eC1218SessionStatus;

typedef enum
{
    E_FIRST_REQUEST_FRAME,
    E_SINGLE_RESPONSE_FRAME,
    E_MULTI_RESPONSE_FRAME,
    E_DUPLICATED_FRAME,
    E_LAST_RESPONSE_FRAME
}eFrameType;

typedef enum
{
    E_BAUDRATE_0        = 0x00,
    E_BAUDRATE_300      = 0x01,
    E_BAUDRATE_600      = 0x02,
    E_BAUDRATE_1200     = 0x03,
    E_BAUDRATE_2400     = 0x04,
    E_BAUDRATE_4800     = 0x05,
    E_BAUDRATE_9600     = 0x06,
    E_BAUDRATE_14400    = 0x07,
    E_BAUDRATE_19200    = 0x08,
    E_BAUDRATE_28800    = 0x09,
    E_BAUDRATE_57600    = 0x0A,
    E_BAUDRATE_38400    = 0x0B,
    E_BAUDRATE_115200   = 0x0C,
    E_BAUDRATE_128000   = 0x0D,
    E_BAUDRATE_256000   = 0x0E,
    E_BAUDRATE_NONE,
} eBaudrateType;

/*PSEM frame control byte*/
typedef union
{
    uint8 byte;
	struct
	{
		uint8 MULTI_FRAME_FLAG:1;
		uint8 FIRST_FRAME_IN_MULTI_FRAME_FLAG:1;
		uint8 TOGGLE_FLAG:1;
		uint8 RESERVED:3;
		uint8 DATA_FORMAT:2;
	}bits;
} stPsemCtlByte;

/*info of PSEM frame*/
typedef struct
{
    uint8 ackType;
    uint8 deviceId;
    stPsemCtlByte ctlByte;
    uint8 frameCnt;
    uint8 headerSize;
    u8_16_t dataLen;
    u8_16_t frameCrcVal;
} stPsemInfo;

/*structure for EPSEM payload*/
typedef struct
{
    uint8 *pData;
    uint16 nSize;
    uint8 chkSum;
} stPsemPayload;

typedef struct
{
    u8_16_t nMaxBytes;
    uint8  nMaxFrames;
    eBaudrateType  nBaudrate;
} stNegotiateService;

//---------------------------------function declare---------------------------------------------------------//
void InitC1218PsemInfo(void);
uint8 CheckC1218ReqFrameCrc(uint8 *pReqData, uint16 size);
uint8 *ParseC1218PsemFrame(uint8 *pReqFrame);
void BuildC1218PsemFrame(stPsemPayload *pPayload, uint8 *pRespData);
void BuildC1218Resp(uint8 *pReqData, uint8 *pRespData);
void BuildC1218Payload(uint8 *pReqData, stPsemPayload *pPsemData);


#if (SW_SIMULATION == 1)
uint8 TestC1218SingleFrame(uint8 *test_data);
#endif

#endif // ANSI_C_1218_H
