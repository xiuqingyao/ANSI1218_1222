#ifndef ANSI_C_1222_H
#define ANSI_C_1222_H

#include "typedef.h"
#include "ansi_def.h"

/*macros for constant value*/
#define MAX_DECODE_LEN               (4)
#define C1222_TAG_SIZE               (sizeof(uint8))

#define EPSEM_PAYLOAD_SIZE           (64)
#define EPSEM_FRAME_HEADER_SIZE      (10)
#define EPSEM_ED_CLASS_SIZE          (4)

#define ACSE_KEY_LEN                 (16)
#define ACSE_REQ_AUTH_IV_LEN         (4)
#define ACSE_RESP_AP_CONTENT_SIZE    (10)
#define ACSE_REQ_AP_TITLE_SIZE       (127)

#define CODE_C1222_STP               0x60
#define CODE_C1222_STD               0x03
#define CODE_C1222_VER			     0x02

/*
* ANSI c12.22 tag-id
*/
typedef enum{
    E_PROTOCOL_VER                  = 0xA0,  //version1
    E_ASO_CONTENT                   = 0xA1,  //ASO-context-name
    E_CALLED_AP_TITLE               = 0xA2,  //Called AP-title
    E_CALLED_AP_QUALIFIER           = 0xA3,  //Called AE-qualifier
    E_CALLED_AP_INVOCATION_ID       = 0xA4,  //Called AP-invocation-id
    E_CALLED_AE_INVOCATION_ID       = 0xA5,  //Called AE-invocation-id
    E_CALLING_AP_TITLE              = 0xA6,  //Calling AP-title
    E_CALLING_AP_QUALIFIER          = 0xA7,  //Calling AE-qualifier
    E_CALLING_AP_INVOCATION_ID      = 0xA8,  //Calling AP-invocation-id
    E_CALLING_AE_INVOCATION_ID      = 0xA9,  //Calling AE-invocation-id
    E_MECHANISM_NAME_ID             = 0x8B,  //Mechanism-name
    E_AUTHENTICATION_VALUE_ID       = 0xAC,  //Authentication-value
    E_AUTHENTICATION_VALUE_EXT_ID   = 0xA2, //calling-authentication-value-external
    E_AUTHENTICATION_VALUE_ASN1_ID  = 0xA0, //calling-authentication-value-single-asn1
    E_AUTHENTICATION_VALUE_C1222_ID = 0xA1, //calling-authentication-value-c1222
    E_P_CONTEXT                     = 0xAE,  //default-P-context
    E_IMPLEMENTATION_INFO           = 0x1D,  //GraphicString
    E_USER_INFO_ELEMENT             = 0xBE,  //user-information-element
    E_USER_INFO_EXT                 = 0x28,  //user-information-external
    E_USER_INFO_OCT_STR             = 0x81,  //user-information-octet-string
}ENUM_ANSI_C1222_TAG;

typedef enum
{
    E_STATE_OFFLINE = 0,
    E_STATE_IDLE,
    E_STATE_SESSIONLESS,
    E_STATE_SESSION,
    E_STATE_NONE,
}eC1222SessionStatus;

typedef enum
{
    E_ED_CLASS_EXCLUDED = 0,
    E_ED_CLASS_INCLUDED,
    E_ED_CLASS_NONE,
}eEdClass;

typedef enum
{
    E_SEC_TYPE_UNSECURED = 0,
    E_SEC_TYPE_AUTH,
    E_SEC_TYPE_AUTH_ENCRPTED,
    E_SEC_TYPE_NONE,
}eSecType;

typedef enum
{
    E_EPSEM_ALWAYS_RESP = 0,
    E_EPSEM_ON_EXCEPTION,
    E_EPSEM_NEVER_RESP,
    E_EPSEM_NONE,
}eEpsemRespType;

typedef union
{
    uint8 byte;
	struct
	{
		uint8 RESPONSE_CONTROL:2;
		uint8 SECURITY_MODE:2;
		uint8 ED_CLASS_INCLUDED:1;
		uint8 PROXY_SERVICE_USED:1;
		uint8 RECOVERY_SESSION:1;
		uint8 Reserved:1;
	}bits;
}stEpsemCtrlByte;

typedef struct
{
    stEpsemCtrlByte ctrlByte;
    eC1222SessionStatus status;
    uint16 errCode;
    uint16 totalPduSize;
    uint16 pduOffset;
    uint16 segPduSize;
}stAnsiC1222Status;

/*structure for authentication element*/
typedef struct
{
    uint8 keyId;
    uint8 iv[ACSE_REQ_AUTH_IV_LEN];
    uint16 nSize;
} stAuthValueElement;

/*response structure for ApTitle*/
typedef struct
{
    uint8 pData[ACSE_REQ_AP_TITLE_SIZE];
    uint16 nSize;
} stApTitleElement;

/*response structure for ApID*/
typedef struct
{
    uint8 pData[ACSE_RESP_AP_CONTENT_SIZE];
    uint16 nSize;
} stApIdElement;

/*response structure for ACSE element*/
typedef struct
{
    uint8 *pData;
    uint16 nSize;
} stElement;

typedef struct
{
    uint8 pData[ACSE_KEY_LEN];
    uint16 nSize;
} stSecElement;

typedef struct
{
    uint8 edClass[EPSEM_ED_CLASS_SIZE];
    uint16 nSize;
} stEpsemEdClass;

/*structure for EPSEM payload*/
typedef struct
{
    uint8 pData[EPSEM_PAYLOAD_SIZE];
    uint16 nSize;
    uint8 chkSum;
} stEpsemPayload;

/*structure for EPSEM element*/
typedef struct
{
    uint8 pHeader[EPSEM_FRAME_HEADER_SIZE];
    stEpsemPayload *pEpsemPayload;
    uint16 nSize;
} stEpsemFrame;

/*structure for logon service*/
typedef struct
{
    uint16 userId;
    uint8 userName[10];
    uint16 nSessionIdleTimeout;
} stLogonService;

/*structure for security service*/
typedef struct
{
    uint8 passwd[20];
    uint16 userId;
} stSecurityService;

/*structure for wait service*/
typedef struct
{
    uint8 time;
} stWaitService;

/*structure for read service*/
/*
typedef struct
{
    uint16 tableId;
    uint32 offset;
    uint16 cnt;
} stReadService;
*/

#if 0
/*ClearText*/
typedef struct
{
    uint8 *pasoContextElem;
    uint8 *pasoContextElem;
}stAcseClearText;

/*PlainText*/
typedef struct
{

}stAcsePlainText;
#endif

//------------------------------------------------------------------
/*structure for EPSEM payload*/
typedef struct
{
    uint8 pData[1024];
    uint16 nSize;
} stTestData;

//-------------------------------------------------------------------

//---------------------------------function declare---------------------------------------------------------//
uint32 ap_title_parse(void *pData, stApTitleElement *pTitleElem, int32 *taglen);
uint32 ap_id_parse(void *pData, stApIdElement *pIdElem, int32 *taglen);
uint32 usrinfo_parse(void *pData, stElement *pEpsemData, int32 *taglen);
uint16 ber_uid_encode(uint8 *ptr, int32 len, int32 tag, uint8 *pData);
uint8 *ber_uid_decode(void *pData, void *pResult);
int32 ber_len_size(int32 n);
int32 ber_len_encode(void * ptr, int32 len, int32 mx);
int32 ber_len_decode(void *pData, int32 *pSize);
int32 ParseC1222AcsePdu(uint8* pData);
uint8 *ParseC1222EpsemFrame(uint8 *pData);
int32 BuildC1222AcsePdu(stEpsemFrame *pEpsemData, uint8 *pAcseData);
//void copy_to(int32 * dst, void * source, int32 len);
void InitC1222AcseInfo(void);
void addAPtoRawData(uint8 * buf, uint8 header, int32 e_len, int32 e_blen, stElement *value, uint32 offset);
void addUserInfoToRawData(void *pData, long nSize);
uint16 auth_parse(void *pData, stAuthValueElement *pValue/*, int32 *berlen*/);
uint32 authvalue_parse(void *pData, stAuthValueElement *pAuthVal, int32 *berlen);

#if (SW_SIMULATION == 1)
uint8 TestC1222SingleFrame(uint8 *test_data);
#endif

#endif // ANSI_C_1222_H
