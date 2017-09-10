//--------------------------------- include files -------------------------------------------------------//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "ansi_c1222.h"
#include "ansi_tblmgr.h"

//--------------------------------- variable declare ---------------------------------------------------------//
stApTitleElement g_calling_title, g_called_title, sec4CalA6;
stApIdElement g_calling_id, g_called_id, g_calling_ae_qulifier;
stAuthValueElement g_authValueElem;
stEpsemEdClass g_epsem_EdClass;
stElement g_user_info;
stEpsemPayload g_epsem_data;
stSecElement g_acse_key;
stAnsiC1222Status g_ansiC1222Status;

//just for test***************************
stTestData g_output_data;
uint8 testKey[16] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
//***************************

//--------------------------------- function declare ---------------------------------------------------------//
/**
 * parse AP-title
 *
 * @param pData user info raw data
 * @param pTitleElem title element
 * @param taglen id element length
 */
uint32 ap_title_parse(void *pData, stApTitleElement *pTitleElem, int32 *taglen)
{
    uint8 *ptr = (uint8 *)pData;
	uint8 *pRet = NULL;

    pTitleElem->nSize = ber_len_decode(ptr + C1222_TAG_SIZE, taglen);
    ptr = ptr + C1222_TAG_SIZE + *taglen;

    if (*ptr == 0x80 || *ptr == 0x02)
    {
        pRet = ber_uid_decode(ptr + C1222_TAG_SIZE, pTitleElem->pData);
    }

	return pTitleElem->nSize;
}

/**
 * parse AP-invocation-id
 *
 * @param pData user info raw data
 * @param pIdElem id element
 * @param taglen id element length
 */
uint32 ap_id_parse(void *pData, stApIdElement *pIdElem, int32 *taglen)
{
    uint8 *ptr = (uint8 *)pData;
	uint8 *pRet = NULL;

    pIdElem->nSize = ber_len_decode(ptr + C1222_TAG_SIZE, taglen);
    ptr = ptr + C1222_TAG_SIZE + *taglen;

    if (*ptr == 0x80 || *ptr == 0x02)
    {
        pRet = ber_uid_decode(ptr + C1222_TAG_SIZE, pIdElem->pData);
    }

	return pIdElem->nSize;
}

/**
 * parse authentication key-id & iv element
 *
 * @param pData user info raw data
 * @param pIdElem id element
 * @param berlen id element length
 */
uint16 auth_parse(void *pData, stAuthValueElement *pValue)
{
    uint8 *ptr = (uint8 *)pData;
	int32 element_len = 0, element_tagLen = 0;

    if (*ptr == 0x80)//key id
    {
        element_len = ber_len_decode(ptr + C1222_TAG_SIZE, &element_tagLen);//external size
        memcpy(&pValue->keyId, ptr + element_tagLen + C1222_TAG_SIZE, element_len);
        pValue->nSize = element_len;
        ptr = ptr + C1222_TAG_SIZE + element_tagLen + element_len;//skip header
    }

    if (*ptr == 0x81)//iv
    {
        element_len = ber_len_decode(ptr + C1222_TAG_SIZE, &element_tagLen);//external size
        memcpy(pValue->iv, ptr + element_tagLen + C1222_TAG_SIZE, element_len);
        pValue->nSize += element_len;
        ptr = ptr + C1222_TAG_SIZE + element_tagLen + element_len;//skip header
    }

	return pValue->nSize;
}

/**
 * parse authentication value
 *
 * @param pData user info raw data
 * @param pEpsemData output epsem data
 * @param berlen output epsem data length
 */
uint32 authvalue_parse(void *pData, stAuthValueElement *pAuthVal, int32 *taglen)
{
    uint8 * ptr = (uint8 *)pData;
    int32 element_len = 0, element_tagLen = 0;

    /*authentication total size*/
    element_len = ber_len_decode(ptr + C1222_TAG_SIZE, &element_tagLen);
    *taglen = element_tagLen;

    /*point user_info_external*/
    ptr = ptr + C1222_TAG_SIZE + element_tagLen;

    /*check header for calling-authentication-value-external*/
    if(*ptr == 0xA2)
    {
        ber_len_decode(ptr + C1222_TAG_SIZE, &element_tagLen);//external size
        ptr = ptr + C1222_TAG_SIZE + element_tagLen;
    }

    /*check header for calling-authentication-value-single-asn1*/
    if(*ptr == 0xA0)
    {
        ber_len_decode(ptr + C1222_TAG_SIZE, &element_tagLen);//external size
        ptr = ptr + C1222_TAG_SIZE + element_tagLen;
    }

    /*check header for calling-authentication-value-c1222*/
    if(*ptr == 0xA1)
    {
        ber_len_decode(ptr + C1222_TAG_SIZE, &element_tagLen);//external size
        ptr = ptr + C1222_TAG_SIZE + element_tagLen;
    }

    auth_parse(ptr, &g_authValueElem);

    return element_len;
}

/**
 * parse user-info
 *
 * @param pData user info raw data
 * @param pEpsemData output epsem data
 * @param taglen output epsem data length
 */
uint32 usrinfo_parse(void *pData, stElement *pEpsemData, int32 *taglen)
{
    uint8 * ptr = (uint8 *)pData;
    int32 element_tagLen = 0;

    /*user-info element size*/
    ber_len_decode(ptr + C1222_TAG_SIZE, &element_tagLen);
    *taglen = element_tagLen;

    /*apply security algorithm*/
    CMacNext(ptr, C1222_TAG_SIZE + element_tagLen);

    /*point user_info_external*/
    ptr = ptr + C1222_TAG_SIZE + element_tagLen;

    /*check header for user-info external*/
    if(*ptr == 0x28)
    {
        ber_len_decode(ptr + C1222_TAG_SIZE, &element_tagLen);//external size

        /*apply security algorithm*/
        CMacNext(ptr, C1222_TAG_SIZE + element_tagLen);

        ptr = ptr + C1222_TAG_SIZE + element_tagLen;
    }

    /*check header for user info octet string*/
    if(*ptr == 0x81)
    {
        pEpsemData->nSize = ber_len_decode(ptr + C1222_TAG_SIZE, &element_tagLen);//octet size

        /*apply security algorithm*/
        CMacNext(ptr, C1222_TAG_SIZE + element_tagLen);

        pEpsemData->pData = ptr + C1222_TAG_SIZE + element_tagLen;//now, pData points epsem data
    }

    return pEpsemData->nSize;
}

/**
 * encode universal identifier
 * relative calling aptitle encode
 *
 * @param ptr raw data starting with length of data
 * @param len length of byte
 * @param tag c1222 tag
 * @param pData result data
 */
uint16 ber_uid_encode(uint8 *ptr, int32 len, int32 tag, uint8 *pData)
{
    uint8 *idPtr[20];
    uint8 totalSize = 0;
    uint8 count = 0;
    uint8 *p = pData + 2;

    uint8 dup[15];
    uint8 oid[15];
	int32 intVal;

    int32 encodeSize = 0, i = 0;

    memset(dup, 0x00, sizeof(dup));
    strncpy((char*)dup, (char*)ptr, len);
    dup[len] = '\0';

    /*store pointer to each value*/
    idPtr[count] = (uint8 *)strtok((char*)dup, ".");
    while(idPtr[count] != NULL)
    {
        count++;
        idPtr[count] = (uint8 *)strtok(NULL, ".");
    }

    /*encode object ID*/
    memset(oid, 0x00, sizeof(oid));
    for(i = 0; i < count; i++)
    {
        intVal = atoi((char*)idPtr[i]);

        /*encode OID*/
        oid[encodeSize++] = intVal & 0x7f;
        while( intVal >>= 7 )
        {
            oid[encodeSize++] = intVal | 0x80;
        }

        /*reverse encoded OID and add encoded OID length to total size*/
        do{
            //encodeSize--;
            p[totalSize++] = oid[--encodeSize];
        }while(encodeSize);
    }

    /*header and size*/
    pData[0] = tag;
    pData[1] = totalSize;//totalSize cannot exceed 127 bytes

    return (2 + totalSize);
}

/**
 * decode universal identifier
 * relative calling aptitle decode
 *
 * @param data encoded raw data starting with length of data
 * @param size (outbound) length of byte
 */
uint8 *ber_uid_decode(void *pData, void *pResult)
{
    int32 nSize = 0;
    uint32 val = 0;//temporary holder for value
    uint8 *ret = pResult;//max 127 bytes of data (defined in c1222 doc)

    uint8 *origin = (uint8 *)pData + 1;
    uint8 *ptr = (uint8 *)pData ;
    nSize = *ptr++;

    for(; ptr < origin + nSize; ++ptr)
    {
        //if MSB is 0, it is short value, encoded on one byte
        if(*ptr >> 7 == 0)
        {
            sprintf((char*)ret + strlen((char*)ret), "%u", *ptr);
        }
        else//otherwise, it is long value, encoded on multiple bytes
        {
            val = *ptr & 0x7f;
            while( *ptr++ & 0x80 )
            {
              val <<= 7;
              val |= *ptr & 0x7f;
            }
            sprintf((char*)ret + strlen((char *)ret), "%u", val);
        }
        strcat((char *)ret, ".");
    }

    ret[strlen((char *)ret) - 1] = '\0';
    return ret;
}

/**
 * Calculate length to be used in BER
 *
 * @param length
 * @return BER length
 */
int32 ber_len_size(int32 n)
{
    int32 len = 1; //byte length

    if(n > 0x7f) len++;
    if(n > 0xff) len++;
    if(n > 0xffff) len++;
    if(n > 0xffffff) len++;
    return len;
}

/**
 * length field  encoding
 *
 * @param pTagLen tag length of element
 * @param len length used by bar
 * @param mx max
 *
 * @return length of ber encoding
 */
int32 ber_len_encode(void *pTagLen, int32 len, int32 mx)
{
    int32 encodeLen = ber_len_size(len), i = 0;
    uint8 * bptr = (uint8 *)pTagLen;

    if(encodeLen > mx) //encode length exceed max
    {
        return 0;
    }

    if(encodeLen == 1) //use number itself
    {
        *bptr = len;
    }
    else
    {
        //number of byte after header
        *bptr = (encodeLen - 1) | 0x80;

        for(i = encodeLen - 2; i >= 0; i--)
        {
            *bptr++ = (len >> (i * 8)) & 0xFF;
        }
    }

    return encodeLen;
}

/**
 * length decoding
 *
 * @param pData source data
 * @param pSize BER encode bytes
 * @return actual length
 * */
int32 ber_len_decode(void *pData, int32 *pSize)
{
    int32 ret = 0, i = 0;
    uint8 *bptr = (uint8 *)pData;

    if(*bptr <= 0x7f)
    {
        ret |= *bptr;
        *pSize = 1;
    }
    else
    {
        *pSize = *bptr & 0x0F;
        bptr++;
        for(i = *pSize-1; i >= 0; i--)
        {
            ret |= (0xFF & *bptr++) << (i * 8);
        }
    }

    return ret;
}


/**
 * @param pointer to buffer containing data
 * @param offset beginning of data
 * @param length of data to be checked
 *
 * @return check sum value
 */
/*
int checksum(void * ptr, int offset, int len)
{
    int sum = 0;
    for(int i = 0; i < len; i++)
        sum += ptr[offset++];
    return (((sum - 1) & 0xFF) ^ 0xFF);
}
void copy_to(int32 * dst, void * source, int32 len)
{
    uint8 * ptr = (uint8 *)source;
    int32 i = 0;
    for(i = len - 1; i >= 0; i--)
    {
        *dst |= (*ptr++) << (i * 8);
    }
}
*/

/**
 * init global variable
 *
 * @param pData: received c12.22 data
 */
void InitC1222AcseInfo(void)
{
    memset(&g_calling_title, 0x00, sizeof(g_calling_title));
    memset(&g_calling_id, 0x00, sizeof(g_calling_id));
    memset(&g_called_title, 0x00, sizeof(g_called_title));
    memset(&g_called_id, 0x00, sizeof(g_called_id));
    memset(&g_user_info, 0x00, sizeof(g_user_info));
	memset(&g_epsem_data, 0x00, sizeof(g_epsem_data));
	memset(&g_epsem_EdClass, 0x00, sizeof(g_epsem_EdClass));

	/*set called AP-id(which is current AP-id)*/
	g_called_id.nSize = 1;
	g_called_id.pData[0] = 0x30;//ASCII format, '0'

	/*init epsem control byte*/
	g_ansiC1222Status.ctrlByte.byte = 0x80;

	/*get encrypt key from table */
#if 0
	//TODO: need to be modified here
	tagN.nSize = ACSE_KEY_LEN;
	memset(tagN.pData, 0x00, ACSE_KEY_LEN);
	tagC.nSize = ACSE_KEY_LEN;
	memset(tagC.pData, 0x00, ACSE_KEY_LEN);
	T.nSize = ACSE_KEY_LEN;
	memset(T.pData, 0x00, ACSE_KEY_LEN);
#endif

    g_acse_key.nSize = ACSE_KEY_LEN;
    memcpy(g_acse_key.pData, testKey, ACSE_KEY_LEN);
    CMacStart(g_acse_key.pData, 'D');
}

/**
 * parse ACSE PDU
 *
 * @param pData: received c12.22 data
 */
int32 ParseC1222AcsePdu(uint8* pData)
{
    uint8 *ptr = (uint8 *)pData;
    int32 pdusize = 0;
    int32 element_len = 0, element_tagLen = 0;

    if(*ptr != 0x60)//stop parse when current frame is not ACSE frame
    {
        //Error packet
        //error = -1;
        return 0;
    }

    element_len = ber_len_decode(ptr + C1222_TAG_SIZE, &element_tagLen);
    ptr = ptr + C1222_TAG_SIZE + element_tagLen; //now pointing elements

    //ACSE data length
    pdusize = C1222_TAG_SIZE + element_tagLen;

    if(*ptr == 0xA1)//aSO-context-element
    {
        /*apply security algorithm on 0xA1*/
        //TODO:......
        //CMacNext(ptr, C1222_TAG_SIZE + element_tagLen + element_len);
    }

    if(*ptr == 0xA2)//Called AP title
    {
        element_len = ap_title_parse(ptr, &g_called_title, &element_tagLen);
        pdusize += C1222_TAG_SIZE + element_tagLen + element_tagLen;

        /*apply security algorithm on 0xA2*/
        CMacNext(ptr, C1222_TAG_SIZE + element_tagLen + element_len);

        ptr = ptr + C1222_TAG_SIZE + element_tagLen + element_len;
    }

    if(*ptr == 0xA4)//Called AP invocation id
    {
        element_len = ap_id_parse(ptr, &g_called_id, &element_tagLen);
        pdusize += C1222_TAG_SIZE + element_tagLen + element_len;

        /*apply security algorithm on 0xA4*/
        CMacNext(ptr, C1222_TAG_SIZE + element_tagLen + element_len);

        ptr = ptr + C1222_TAG_SIZE + element_tagLen + element_len;
    }

    if(*ptr == 0xA6)//Calling AP title
    {
		element_len = ap_title_parse(ptr, &g_calling_title, &element_tagLen);

        /*copy value from 0xA6 to calculate security calculation*/
        memcpy(sec4CalA6.pData, ptr, C1222_TAG_SIZE + element_tagLen + element_len);
        sec4CalA6.nSize = C1222_TAG_SIZE + element_tagLen + element_len;

        ptr = ptr + C1222_TAG_SIZE + element_tagLen + element_len;
        pdusize += C1222_TAG_SIZE + element_tagLen + element_len;
    }

    if(*ptr == 0xA7)//calling-AE-qualifier-element
    {
        element_len = ap_id_parse(ptr, &g_calling_ae_qulifier, &element_tagLen);
        pdusize += C1222_TAG_SIZE + element_tagLen + element_len;

        /*apply security algorithm on 0xA8*/
        CMacNext(ptr, C1222_TAG_SIZE + element_tagLen + element_len);

        ptr = ptr + C1222_TAG_SIZE + element_tagLen + element_len;
    }

    if(*ptr == 0xA8)//Calling AP invocation id
    {
        element_len = ap_id_parse(ptr, &g_calling_id, &element_tagLen);
        pdusize += C1222_TAG_SIZE + element_tagLen + element_len;

        /*apply security algorithm on 0xA8*/
        CMacNext(ptr, C1222_TAG_SIZE + element_tagLen + element_len);

        ptr = ptr + C1222_TAG_SIZE + element_tagLen + element_len;
    }

    if(*ptr == 0x8B)//mechanism-name
    {

    }

    if(*ptr == 0xAC)//Authentication-value
    {
        element_len = authvalue_parse(ptr, &g_authValueElem, &element_tagLen);
        pdusize += C1222_TAG_SIZE + element_tagLen + element_len;

        /*apply security algorithm on 0xAC*/
        CMacNext(ptr, C1222_TAG_SIZE + element_tagLen + element_len);

        ptr = ptr + C1222_TAG_SIZE + element_tagLen + element_len;
    }

    //if calling id is not present, stop process
    if(g_calling_id.nSize == 0 && g_calling_id.pData == NULL)
    {
        //Calling id is not present, abort parsing
        //error = -2;
        return 0;
    }

    //parse user information
    if(*ptr == 0xBE)
    {
        element_len = usrinfo_parse(ptr, &g_user_info, &element_tagLen);
        pdusize += C1222_TAG_SIZE + element_tagLen + element_len;
        ptr = ptr + C1222_TAG_SIZE + element_tagLen + element_len;//element "user-info" start from here
    }
    else
    {
        //User info Header is not present, abort
        //error = -3;
    }

    return pdusize;
}

/**
 * parse EPSEM frame
 *
 * @param pData: received c12.22 data
 */
uint8 *ParseC1222EpsemFrame(uint8 *pData)
{
    uint8 * ptr = (uint8 *)pData;
    int32 element_len = 0, element_tagLen = 0;
    uint8 secFlag = 0x00;
    uint8 macVal[4] = {0}, T[16] = {0}, tagN[16] = {0}, tagC[16] = {0};
    uint16 i = 0;

    if(*ptr == 0x00)
    {
        /*invalid EPSEM*/
        return NULL;
    }
    g_ansiC1222Status.ctrlByte.byte = *ptr;//first byte is EPSEM-Control

    /*security mode*/
    if ((g_ansiC1222Status.ctrlByte.bits.SECURITY_MODE == E_SEC_TYPE_AUTH) ||
        (g_ansiC1222Status.ctrlByte.bits.SECURITY_MODE == E_SEC_TYPE_AUTH_ENCRPTED))
    {
        secFlag = 0x01;

        CMacNext(&g_ansiC1222Status.ctrlByte.byte, sizeof(g_ansiC1222Status.ctrlByte.byte));//apply security algorithm on EPSEM-Control
        CMacNext(sec4CalA6.pData, sec4CalA6.nSize);//apply security algorithm on 0xA6
        CMacNext(&g_authValueElem.keyId, sizeof(g_authValueElem.keyId));//apply security algorithm on key-id
        CMacNext(g_authValueElem.iv, sizeof(g_authValueElem.iv));//apply security algorithm on iv
    }

    /*ed-class*/
    if (g_ansiC1222Status.ctrlByte.bits.ED_CLASS_INCLUDED == E_ED_CLASS_INCLUDED)//if ed_class is present
    {
        /*copy ed-class*/
        memcpy(g_epsem_EdClass.edClass, ptr + C1222_TAG_SIZE, EPSEM_ED_CLASS_SIZE);
        g_epsem_EdClass.nSize = EPSEM_ED_CLASS_SIZE;

        element_len = ber_len_decode(ptr + C1222_TAG_SIZE + g_epsem_EdClass.nSize, &element_tagLen);

        /*apply security algorithm on <key-id>, <iv>, <ed-class>, <epsem-data>, <padding>*/
        if (g_ansiC1222Status.ctrlByte.bits.SECURITY_MODE == E_SEC_TYPE_AUTH)//clear_text + mac
        {
            CMacNext(g_epsem_EdClass.edClass, sizeof(g_epsem_EdClass.edClass));//apply security algorithm on Ed-class
            CMacNext(ptr + C1222_TAG_SIZE + g_epsem_EdClass.nSize, element_len);//apply security algorithm on EPSEM-data
            CMacEnd(tagN);//finish calculation, get tagN

            /* calculate tagC*/
            /* Encryption of the paylaod */
            AesCtr(g_acse_key.pData, tagN, ptr + C1222_TAG_SIZE, element_len + g_epsem_EdClass.nSize);
            CMacStart(g_acse_key.pData, 'Q');
            CMacNext(ptr + C1222_TAG_SIZE + g_epsem_EdClass.nSize, element_len);
            CMacEnd(tagC);

            for (i = 0; i < 16; i++)
            {
                T[i] = tagN[i] ^ tagC[i];
            }

            #if 0
            printf("\r\n==With ed-class, ClearText+MAC:==");
            printf("\r\nTagN:");
            for (i = 0; i < 16; i++)
            {
                printf("%02x", tagN[i]);
            }
            printf("\r\nTagC:");
            for (i = 0; i < 16; i++)
            {
                printf("%02x", tagC[i]);
            }
            printf("\r\nT:");
            for (i = 0; i < 16; i++)
            {
                printf("%02x", T[i]);
            }
            printf("\r\n================================\r\n");
            #endif
        }
        else if (g_ansiC1222Status.ctrlByte.bits.SECURITY_MODE == E_SEC_TYPE_AUTH_ENCRPTED)//cipher_text + mac
        {
#if 0
            CMacNext(g_epsem_EdClass.edClass, sizeof(g_epsem_EdClass.edClass));//apply security algorithm on Ed-class
            CMacNext(ptr + C1222_TAG_SIZE + g_epsem_EdClass.nSize, element_len);//apply security algorithm on EPSEM-data
            CMacEnd(tagN);//finish calculation
#endif
        }

        /*skip tag*/
        ptr = ptr + C1222_TAG_SIZE + g_epsem_EdClass.nSize + element_tagLen;
    }
    else //if ed_class is not present
    {
        element_len = ber_len_decode(ptr + C1222_TAG_SIZE, &element_tagLen);

        /*apply security algorithm on <key-id>, <iv>, <epsem-data>, <padding>*/
        if (g_ansiC1222Status.ctrlByte.bits.SECURITY_MODE == E_SEC_TYPE_AUTH)//clear_text + mac
        {
            CMacNext(ptr + C1222_TAG_SIZE, element_len);//apply security algorithm on EPSEM-data
            CMacEnd(tagN);//finish security calculation, get tagN

            /* calculate tagC*/
            /* Encryption of the paylaod */
            AesCtr(g_acse_key.pData, tagN, ptr + C1222_TAG_SIZE, element_len);
            CMacStart(g_acse_key.pData, 'Q');
            CMacNext(ptr + C1222_TAG_SIZE, element_len);
            CMacEnd(tagC);

            for (i = 0; i < 16; i++)
            {
                T[i] = tagN[i] ^ tagC[i];
            }

            #if 0
            printf("\r\n==No ed-class, ClearText+MAC:==");
            printf("\r\nTagN:");
            for (i = 0; i < 16; i++)
            {
                printf("%02x", tagN[i]);
            }
            printf("\r\nTagC:");
            for (i = 0; i < 16; i++)
            {
                printf("%02x", tagC[i]);
            }
            printf("\r\nT:");
            for (i = 0; i < 16; i++)
            {
                printf("%02x", T[i]);
            }
            printf("\r\n================================\r\n");
            #endif
        }
        else if (g_ansiC1222Status.ctrlByte.bits.SECURITY_MODE == E_SEC_TYPE_AUTH_ENCRPTED)//cipher_text + mac
        {
#if 0
            CMacNext(g_epsem_EdClass.edClass, sizeof(g_epsem_EdClass.edClass));//apply security algorithm on Ed-class
            CMacNext(ptr + C1222_TAG_SIZE + g_epsem_EdClass.nSize, element_len);//apply security algorithm on EPSEM-data

            CMacEnd(tagN);//finish calculation
#endif
        }

        /*skip tag*/
        ptr = ptr + C1222_TAG_SIZE + element_tagLen;
    }

    if (secFlag)
    {
        /*save MAC value*/
        memcpy(macVal, ptr, 4);
    }

    return ptr;
}


/**
 * build ACSE PDU
 *
 * @param pEpsemData: input epsem data
 * @param pAcseData: output acse data
 */
int32 BuildC1222AcsePdu(stEpsemFrame *pEpsemData, uint8 *pAcseData)
{
    ///////////////////////////////////////////////////////////////
    //                                                           //
    //              calculate all sizes and offsets              //
    //               and encoded data (bottom up)               //
    //                                                           //
    ///////////////////////////////////////////////////////////////
    /*calculate full PDU size*/
    int32 acsepdu_len = 0, acsepdu_tagLen = 0;
	int32 pdusize = 0;

    /*calculate "user info" field*/
    int32 epsemData_len = 0, epsemData_tagLen = 0;
    int32 userinfoOctstr_len = 0, userinfoOctstr_tagLen = 0;
    int32 userinfoExt_len = 0, userinfoExt_tagLen = 0;
    int32 usrinfo_len = 0;

    /*calculate "calling authentication value" field*/
    int32 callingAuthValC1222_len = 0, callingAuthValC1222_tagLen = 0;
    int32 callingAuthValSingleAsn1_len = 0, callingAuthValSingleAsn1_tagLen = 0;
    int32 callingAuthValExternal_len = 0, callingAuthValExternal_tagLen = 0;
    int32 callingAuthVal_len = 0, callingAuthVal_tagLen = 0;
    int32 authval_data_len = 0;
    int32 keyId_len = 0, keyId_tagLen = 0, iv_len = 0, iv_tagLen = 0;
    stAuthValueElement stCallingAuthVal;

    /*encode uid variables*/
    stApTitleElement stCallingTitle, stCalledTitle;
    stApIdElement stCallingId, stCalledId;

    /*variables for encoded length*/
    int32 callingTitle_len = 0, callingTitle_tagLen = 0;
    int32 calledTitle_len = 0, calledTitle_tagLen = 0;
    int32 callingId_len = 0, callingId_tagLen = 0;
    int32 calledId_len = 0, calledId_tagLen = 0;

	/*now copy into buffer*/
    uint8 *raw_data = pAcseData;
	int32 cum_offset = 0;
	uint16 epsem_header_size = 0;
	stElement element;

    /*1.1 calculated 0xBE(user-info) fields*/
    epsemData_tagLen = ber_len_encode(&epsemData_len, pEpsemData->nSize, MAX_DECODE_LEN);
    userinfoOctstr_tagLen = ber_len_encode(&userinfoOctstr_len, C1222_TAG_SIZE + epsemData_tagLen + epsemData_len, MAX_DECODE_LEN);
    userinfoExt_tagLen = ber_len_encode(&userinfoExt_len,  C1222_TAG_SIZE + userinfoOctstr_tagLen + C1222_TAG_SIZE + epsemData_tagLen + epsemData_len, MAX_DECODE_LEN);
    usrinfo_len = C1222_TAG_SIZE + userinfoExt_tagLen + userinfoExt_len;//total user info length(tag(BE) + length of element "user-information-element")

    /*update total PDU size*/
	pdusize += usrinfo_len;

    /*1.2 calculate 0xAC(authentication-value) fields*/
    if(g_authValueElem.nSize != 0)
	{
        keyId_tagLen = ber_len_encode(&keyId_len, sizeof(g_authValueElem.keyId), MAX_DECODE_LEN);
        iv_tagLen = ber_len_encode(&iv_len, sizeof(g_authValueElem.iv), MAX_DECODE_LEN);
        authval_data_len = C1222_TAG_SIZE + keyId_tagLen + keyId_len;//key id total length
        authval_data_len += C1222_TAG_SIZE + iv_tagLen + iv_len;//iv total length

        callingAuthValC1222_tagLen = ber_len_encode(&callingAuthValC1222_len, authval_data_len, MAX_DECODE_LEN);
        authval_data_len = C1222_TAG_SIZE + callingAuthValC1222_tagLen + callingAuthValC1222_len;
        callingAuthValSingleAsn1_tagLen = ber_len_encode(&callingAuthValSingleAsn1_len, authval_data_len, MAX_DECODE_LEN);
        authval_data_len = C1222_TAG_SIZE + callingAuthValSingleAsn1_tagLen + callingAuthValSingleAsn1_len;
        callingAuthValExternal_tagLen = ber_len_encode(&callingAuthValExternal_len, authval_data_len, MAX_DECODE_LEN);
        authval_data_len = C1222_TAG_SIZE + callingAuthValExternal_tagLen + callingAuthValExternal_len;
        callingAuthVal_tagLen = ber_len_encode(&callingAuthVal_len, authval_data_len, MAX_DECODE_LEN);

        pdusize += C1222_TAG_SIZE + callingAuthVal_tagLen + callingAuthVal_len;//total user info length(tag(AC) + length of element "user-information-element")
 	}

	/*1.3 encode 0xA8(AP-calling-id) data from request AP-called-id*/
    memset(&stCallingId, 0x00, sizeof(stCallingId));
	if (g_called_id.nSize != 0)
	{
        stCallingId.nSize = ber_uid_encode(g_called_id.pData, strlen((char *)g_called_id.pData), 0x02, stCallingId.pData);
        callingId_tagLen = ber_len_encode(&callingId_len, stCallingId.nSize, MAX_DECODE_LEN);
        pdusize += C1222_TAG_SIZE + callingId_tagLen + callingId_len;
	}

    /*1.4 encode 0xA6(AP-calling-title) data from request AP-called-title */
    memset(&stCallingTitle, 0x00, sizeof(stCallingTitle));
    if(g_called_title.nSize != 0)
	{
        stCallingTitle.nSize = ber_uid_encode(g_called_title.pData, strlen((char *)g_called_title.pData), 0x80, stCallingTitle.pData);
        callingTitle_tagLen = ber_len_encode(&callingTitle_len, stCallingTitle.nSize, MAX_DECODE_LEN);
        pdusize += C1222_TAG_SIZE + callingTitle_tagLen + callingTitle_len;
    }

	/*1.5 encode 0xA4(AP-called-id) data from request AP-calling-id*/
	memset(&stCalledId, 0x00, sizeof(stCalledId));
    if(g_calling_id.nSize != 0)
	{
        stCalledId.nSize = ber_uid_encode(g_calling_id.pData, strlen((char *)g_calling_id.pData), 0x02, stCalledId.pData);
        calledId_tagLen = ber_len_encode(&calledId_len, stCalledId.nSize, MAX_DECODE_LEN);
        pdusize += C1222_TAG_SIZE + calledId_tagLen + calledId_len;
    }

	/*1.6 encode 0xA2(AP-called-title) data from request AP-calling-title*/
	memset(&stCalledTitle, 0x00, sizeof(stCalledTitle));
    if(g_calling_title.nSize != 0)
	{
        stCalledTitle.nSize = ber_uid_encode(g_calling_title.pData, strlen((char *)g_calling_title.pData), 0x80, stCalledTitle.pData);
        calledTitle_tagLen = ber_len_encode(&calledTitle_len, stCalledTitle.nSize, MAX_DECODE_LEN);
        pdusize += C1222_TAG_SIZE + calledTitle_tagLen + calledTitle_len;
    }

	/*calculated total length*/
    acsepdu_tagLen = ber_len_encode(&acsepdu_len, pdusize, MAX_DECODE_LEN);
    pdusize = C1222_TAG_SIZE + acsepdu_tagLen + acsepdu_len;

    ///////////////////////////////////////////////////////////////
    //                                                           //
    //          start to build ACSE data (top down)              //
    //                                                           //
    ///////////////////////////////////////////////////////////////
    /*2.1 encode tag(0x60) and total ACSE PDU length*/
    raw_data[0] = 0x60;
    memcpy(raw_data + C1222_TAG_SIZE, &acsepdu_len, acsepdu_tagLen);

    /*set offset to next position*/
    cum_offset = C1222_TAG_SIZE + acsepdu_tagLen;

    /*2.2 add called_title element to buffer*/
    memset(&element, 0x00, sizeof(element));
	element.pData = stCalledTitle.pData;
	element.nSize = stCalledTitle.nSize;
    addAPtoRawData(raw_data, 0xA2, calledTitle_len,  calledTitle_tagLen, &element, cum_offset);
    cum_offset += C1222_TAG_SIZE + calledTitle_tagLen + stCalledTitle.nSize;

    /*2.3 add called_id element to buffer*/
	memset(&element, 0x00, sizeof(element));
	element.pData = stCalledId.pData;
	element.nSize = stCalledId.nSize;
    addAPtoRawData(raw_data, 0xA4, calledId_len, calledId_tagLen, &element, cum_offset);
	cum_offset += C1222_TAG_SIZE + calledId_tagLen + stCalledId.nSize;

    /*2.4 add calling_title element to buffer*/
	memset(&element, 0x00, sizeof(element));
	element.pData = stCallingTitle.pData;
	element.nSize = stCallingTitle.nSize;
    addAPtoRawData(raw_data, 0xA6, callingTitle_len, callingTitle_tagLen, &element, cum_offset);
	cum_offset += C1222_TAG_SIZE + callingTitle_tagLen + stCallingTitle.nSize;

    /*2.5 add calling_id element to buffer*/
	memset(&element, 0x00, sizeof(element));
	element.pData = stCallingId.pData;
	element.nSize = stCallingId.nSize;
    addAPtoRawData(raw_data, 0xA8, callingId_len, callingId_tagLen, &element, cum_offset);
    cum_offset += C1222_TAG_SIZE + callingId_tagLen + stCallingId.nSize;

    /*2.6 add authentication_value element to buffer*/
    if (g_authValueElem.nSize != 0)
    {
        raw_data[cum_offset++] = 0xAC;
        memcpy(raw_data + cum_offset, &callingAuthVal_len, callingAuthVal_tagLen);
        cum_offset += callingAuthValExternal_tagLen;

        raw_data[cum_offset++] = 0xA2;
        memcpy(raw_data + cum_offset, &callingAuthValExternal_len, callingAuthValExternal_tagLen);
        cum_offset += callingAuthValExternal_tagLen;

        raw_data[cum_offset++] = 0xA0;
        memcpy(raw_data + cum_offset, &callingAuthValSingleAsn1_len, callingAuthValSingleAsn1_tagLen);
        cum_offset += callingAuthValSingleAsn1_tagLen;

        raw_data[cum_offset++] = 0xA1;
        memcpy(raw_data + cum_offset, &callingAuthValC1222_len, callingAuthValC1222_tagLen);
        cum_offset += callingAuthValC1222_tagLen;

        raw_data[cum_offset++] = 0x80;
        memcpy(raw_data + cum_offset, &keyId_len, keyId_tagLen);
        cum_offset += keyId_tagLen;
        memcpy(raw_data + cum_offset, &g_authValueElem.keyId, keyId_len);
        cum_offset += keyId_len;

        raw_data[cum_offset++] = 0x81;
        memcpy(raw_data + cum_offset, &iv_len, iv_tagLen);
        cum_offset += iv_tagLen;
        memcpy(raw_data + cum_offset, g_authValueElem.iv, iv_len);
        cum_offset += iv_len;
    }

    /*2.7 add user_info element to buffer*/
    raw_data[cum_offset++] = 0xBE;
    memcpy(raw_data + cum_offset, &userinfoExt_len, userinfoExt_tagLen);
    cum_offset += userinfoExt_tagLen;

    raw_data[cum_offset++] = 0x28;
    memcpy(raw_data + cum_offset, &userinfoOctstr_len, userinfoOctstr_tagLen);
    cum_offset += userinfoOctstr_tagLen;

    raw_data[cum_offset++] = 0x81;
    memcpy(raw_data + cum_offset, &epsemData_len, epsemData_tagLen);
    cum_offset += epsemData_tagLen;

    /*encode epsem data(header + epsem data)*/
    epsem_header_size = pEpsemData->nSize - pEpsemData->pEpsemPayload->nSize;
    memcpy(raw_data + cum_offset, pEpsemData->pHeader, epsem_header_size);
	cum_offset += epsem_header_size;
    memcpy(raw_data + cum_offset, pEpsemData->pEpsemPayload->pData, pEpsemData->pEpsemPayload->nSize);

    return pdusize;
}

/**
 * add AP element(Called/Calling AP-title, Called/Calling AP-id) to the frame
 *
 * @param buf: rawdata buffer
 * @param header: header of ap element
 * @param e_len: ap element's encoded length
 * @param e_blem: size of ap element's encoded length
 * @param value: ap element
 * @param offset: offset to be used for buffer
 */
void addAPtoRawData(uint8 * buf, uint8 header, int32 e_len, int32 e_blen, stElement *value, uint32 offset)
{
    if(value != NULL)
    {
        buf[offset++] = header;
        memcpy(buf + offset, &e_len, e_blen);

        offset += e_blen;
        memcpy(buf + offset, value->pData, value->nSize);
        offset += value->nSize;
    }
}

/**
 * build C12.22 response frame
 *
 * @param type: resp type
 * @param serviceCode: service code
 * @param pRespData: output response data
 */
void BuildC1222Resp(uint8 *rx_data, uint8 *pRespData)
{
    stEpsemPayload epsemData;
	stEpsemFrame   epsemFrame;

    /*build EPSEM payload*/
	memset(&epsemData, 0x00, sizeof(epsemData));
	BuildC1222EpsemPayload(rx_data, &epsemData);

	/*build EPSEM frame*/
	memset(&epsemFrame, 0x00, sizeof(epsemFrame));
	BuildC1222EpsemFrame(&epsemData, &epsemFrame);

    /*build ACSE frame*/
    BuildC1222AcsePdu(&epsemFrame, pRespData);
}

/**
 * build EPSEM payload
 *
 * @param type: resp type
 * @param serviceCode: service code
 * @param pEpsemData: output EPSEM data
 */
void BuildC1222EpsemPayload(uint8 *rx_data, stEpsemPayload *pEpsemData)
{
    //if (!pEpsemData)
    //    return;
    uint8 serviceCode = *rx_data++;

    //if (E_RESP_OK == type)
    {
        switch (serviceCode)
        {
            case CODE_IDENTIFICATION://Identification
            	{
    				pEpsemData->pData[0] = CODE_OK;
    				pEpsemData->nSize++;
    				pEpsemData->pData[1] = CODE_C1222_STD;
    				pEpsemData->nSize++;
    				pEpsemData->pData[2] = CODE_C1222_VER;
    				pEpsemData->nSize++;
    				pEpsemData->pData[3] = CODE_REV;
    				pEpsemData->nSize++;
    				pEpsemData->pData[4] = CODE_FEATURE;
    				pEpsemData->nSize++;
    				//TODO:session idle timeout
            	}
                break;
#if 0
    		case CODE_RESOLVE://resolve
    			break;
    		case CODE_TRACE://trace
    			break;
#endif
            case CODE_LOGON://logon
                {
                    stLogonService logonSerData;
                    memset(&logonSerData, 0x00, sizeof(logonSerData));
                    memcpy(&logonSerData, rx_data, sizeof(logonSerData));

    				pEpsemData->pData[0] = CODE_OK;
    				pEpsemData->nSize++;
    				pEpsemData->pData[1] = logonSerData.nSessionIdleTimeout & 0xFF;//convert byte order
    				pEpsemData->nSize++;
    				pEpsemData->pData[2] = (logonSerData.nSessionIdleTimeout >> 8) & 0xFF;
    				pEpsemData->nSize++;
            	}
                break;
            case CODE_READ30://full read
            case CODE_READ3F://partial read
                {
                    u8_16_t tableid;
                    u8_32_t offset;
                    u8_16_t count;
                    uint8 retCode = CODE_OK;

#if (LITTLE_ENDIAN == 1)
                    tableid.b[1] = *rx_data++;//table id
                    tableid.b[0] = *rx_data++;
#else
                    tableid.b[0] = *rx_data++;//table id
                    tableid.b[1] = *rx_data++;
#endif

                    if (CODE_READ3F == serviceCode)
                    {

#if (LITTLE_ENDIAN == 1)
                        offset.b[3] = 0x00;//offset
                        offset.b[2] = *rx_data++;
                        offset.b[1] = *rx_data++;
                        offset.b[0] = *rx_data++;
                        count.b[1] = *rx_data++;//read bytes
                        count.b[0] = *rx_data++;
#else
                        offset.b[0] = 0x00;//offset
                        offset.b[1] = *rx_data++;
                        offset.b[2] = *rx_data++;
                        offset.b[3] = *rx_data++;
                        count.b[0] = *rx_data++;//read bytes
                        count.b[1] = *rx_data++;
#endif // LITTLE_ENDIAN

                    }
                    else
                    {
                        offset.l = 0;
                        count.w = 0x0000;
                    }

                    retCode = PartialRead(serviceCode, tableid.w, offset.l, count.w, pEpsemData->pData, &pEpsemData->nSize, &pEpsemData->chkSum);
                    if (CODE_OK == retCode)
                    {
                        count.w = pEpsemData->nSize;

                        pEpsemData->pData[0] = retCode;
#if (LITTLE_ENDIAN == 1)
                        pEpsemData->pData[1] = count.b[1];
                        pEpsemData->pData[2] = count.b[0];
#else
                        pEpsemData->pData[1] = count.b[0];
                        pEpsemData->pData[2] = count.b[1];
#endif
                        pEpsemData->nSize += 3;
                        pEpsemData->pData[pEpsemData->nSize] = GetChecksum(pEpsemData->chkSum);
                        pEpsemData->nSize++;
                    }
                    else
                    {
                        memset(pEpsemData, 0x00, sizeof(stEpsemPayload));
                        pEpsemData->pData[0] = retCode;
                        pEpsemData->nSize++;
                    }
                }
                break;
            case CODE_WRITE40://full write
            case CODE_WRITE4F://partial write
                {
                    u8_16_t tableid;
                    u8_32_t offset;
                    u8_16_t count;
                    uint8 retCode = CODE_OK;

#if (LITTLE_ENDIAN == 1)
                    tableid.b[1] = *rx_data++;//table id
                    tableid.b[0] = *rx_data++;
#else
                    tableid.b[0] = *rx_data++;//table id
                    tableid.b[1] = *rx_data++;
#endif

                    if (CODE_WRITE4F == serviceCode)
                    {
#if (LITTLE_ENDIAN == 1)
                        offset.b[3] = 0x00;       //offset
                        offset.b[2] = *rx_data++;
                        offset.b[1] = *rx_data++;
                        offset.b[0] = *rx_data++;
                        count.b[1] = *rx_data++;  //count
                        count.b[0] = *rx_data++;
#else
                        offset.b[0] = 0x00;//offset
                        offset.b[1] = *rx_data++;
                        offset.b[2] = *rx_data++;
                        offset.b[3] = *rx_data++;
                        count.b[0] = *rx_data++;//read bytes
                        count.b[1] = *rx_data++;
#endif // LITTLE_ENDIAN

                    }
                    else
                    {
                        offset.l = 0;
#if (LITTLE_ENDIAN == 1)
                        count.b[1] = *rx_data++;  //count
                        count.b[0] = *rx_data++;
#else
                        count.b[0] = *rx_data++;//read bytes
                        count.b[1] = *rx_data++;
#endif // LITTLE_ENDIAN
                    }

                    pEpsemData->pData[0] = PartialWrite(serviceCode, tableid.w, offset.l, count.w, rx_data);
                    pEpsemData->nSize++;
                }
                break;
            case CODE_SECURITY://security
                {
                    //stSecurityService secSerData;
                    //memset(&secSerData, 0x00, sizeof(secSerData));
                    //memcpy(&secSerData, rx_data, sizeof(secSerData));

                    pEpsemData->pData[0] = CODE_OK;
                    pEpsemData->nSize++;
                }
                break;
            case CODE_WAIT://wait
                {
                    //stWaitService waitSerData;
                    //memset(&waitSerData, 0x00, sizeof(waitSerData));
                    //memcpy(&waitSerData, rx_data, sizeof(waitSerData));

                    pEpsemData->pData[0] = CODE_OK;
                    pEpsemData->nSize++;
                }
                break;
            /*
            case CODE_TERMINATE://terminate
            case CODE_LOGOFF://log-off
    		case CODE_DISCONNECT://disconnect
    		case CODE_DEREGISTRATION://deregistration
            case CODE_REGISTRATION://registration
                break;
            */
            default:
                {
                    pEpsemData->pData[0] = CODE_OK;
                    pEpsemData->nSize++;
                }
                break;
    	}
    }
#if 0
	else if (E_RESP_ERR == type)
	{
		switch (serviceCode)
		{
			case CODE_ERR://Rejection request. Reason not provided
				break;
			case CODE_SNS://Service Not supported. Message is valid
				break;
			case CODE_ISC://Insufficient Security clearance
				break;
			case CODE_ONP://Operation not possible. Message is valid, but message could not support
				break;
			case CODE_IAR://Inappropriate Action Request
				break;
			case CODE_BSY://Device busy
				break;
			case CODE_DNR://Data not ready
				break;
			case CODE_DLK://Data Locked
				break;
			case CODE_RNO://Renegotiate Request
				break;
			case CODE_ISSS://Invalid service sequence state
				{
					pEpsemData->pData[0] = CODE_ISSS;
					pEpsemData->nSize++;

					//TODO:session idle timeout
					//......
				}
				break;
			case CODE_SME://Security Mechanism Error
				break;
			case CODE_UAT://Unknown Application Title
				break;
			case CODE_NETT://Network Time-out
				break;
			case CODE_NETR://Network Not Reachable
				break;
			case CODE_RQTL://Request Too Large
				break;
			case CODE_RSTL://Response Too Large
				break;
			case CODE_SGNP://Segmentation not possible
				break;
			case CODE_SGRR://Segmentation error
				break;
		}
	}
#endif
}

/**
 * build EPSEM frame
 *
 * @param type: resp type
 * @param serviceCode: service code
 * @param pEpsemData: output EPSEM frame
 */
void BuildC1222EpsemFrame(stEpsemPayload *pEpsemData, stEpsemFrame *pEpsemFrame)
{
	int32 build_size = 0;
	int32 element_len = 0, element_tagLen = 0;
	uint16 offset = 0;

    /*calculate EPSEM header*/
    /*encode service length*/
    element_tagLen = ber_len_encode(&element_len, pEpsemData->nSize, MAX_DECODE_LEN);

    /*encode element "epsem-control"*/
    pEpsemFrame->pHeader[0] = g_ansiC1222Status.ctrlByte.byte;
    offset += 1;

    /*calculate EPSEM size*/
    if (g_ansiC1222Status.ctrlByte.bits.ED_CLASS_INCLUDED == E_ED_CLASS_INCLUDED)
    {
        /*size = epsem-control(1 byte) + ed-class(4 bytes) + service-length + data-size*/
        build_size = C1222_TAG_SIZE + g_epsem_EdClass.nSize + element_tagLen + element_len;

		/*encode element "ed-class"*/
		memcpy(pEpsemFrame->pHeader + offset, g_epsem_EdClass.edClass, g_epsem_EdClass.nSize);
        offset += g_epsem_EdClass.nSize;
    }
    else
    {
        /*size = epsem-control + service-length + data-size*/
        build_size = C1222_TAG_SIZE + element_tagLen + element_len;
    }

    /*encode element "service-length"*/
    memcpy(pEpsemFrame->pHeader + offset, &element_len, element_tagLen);

    /*set payload info to EPSEM frame*/
	pEpsemFrame->pEpsemPayload = pEpsemData;
	pEpsemFrame->nSize = build_size;
}

//==================================================================================
//==================================================================================
//==================================================================================
//==================================================================================
#if (SW_SIMULATION == 1)
uint8 TestC1222SingleFrame(uint8 *test_data)
{
    uint8 *pUserPsemData = NULL;
    uint16 cnt = 0;

    InitC1222AcseInfo();
    ParseC1222AcsePdu(test_data);
    if (g_user_info.nSize != 0)
    {
        pUserPsemData = ParseC1222EpsemFrame(g_user_info.pData);

        if (g_ansiC1222Status.ctrlByte.bits.RESPONSE_CONTROL == E_EPSEM_ALWAYS_RESP)
        {
            BuildC1222Resp(pUserPsemData, g_output_data.pData);
        }
        else
        {
            printf("\r\nNo need to response, check you epsem control byte(bit0~bit1)!\r\n");
        }
    }

    //print test result when response bit(0~1) is 0
    if (g_ansiC1222Status.ctrlByte.bits.RESPONSE_CONTROL == E_EPSEM_ALWAYS_RESP)
    {
        printf("\r\nrequest data:===================\r\n");
        for (; cnt < (test_data[1] + 2); cnt++)
        {
            printf ("0x%02x ", test_data[cnt]);
            if ((cnt+1)%10 == 0)
                printf("\r\n");
        }
        printf("\r\n");

        printf("\r\nresponse data:==================\r\n");
        for (cnt = 0; cnt < (g_output_data.pData[1] + 2); cnt++)
        {
            printf ("0x%02x ", g_output_data.pData[cnt]);
            if ((cnt+1)%10 == 0)
                printf("\r\n");
        }
        printf("\r\n");
    }

    return 1;
}
#endif
