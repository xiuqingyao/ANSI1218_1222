#ifndef ANSI_DEF_H
#define ANSI_DEF_H

#include "typedef.h"

#define CODE_REV			0x00
#define CODE_FEATURE		0x00

typedef enum{
    CODE_IDENTIFICATION = 0x20,
    CODE_TERMINATE      = 0x21,
    //CODE_DISCONNECT 		= 0x22,//c12.22 used
    //CODE_DEREGISTRATION 	= 0x24,//c12.22 used
    //CODE_RESOLVE 	        = 0x25,//c12.22 used
    //CODE_TRACE 	        = 0x26,//c12.22 used
    //CODE_REGISTRATION 	= 0x27,//c12.22 used
    CODE_READ30         = 0x30,
    CODE_READ3F         = 0x3f,
    CODE_WRITE40        = 0x40,
    CODE_WRITE4F        = 0x4f,
    CODE_LOGON          = 0x50,
    CODE_SECURITY       = 0x51,
    CODE_LOGOFF         = 0x52,
    CODE_NEGOTIATE60    = 0x60,
    CODE_NEGOTIATE61,
    CODE_NEGOTIATE62,
    CODE_NEGOTIATE63,
    CODE_NEGOTIATE64,
    CODE_NEGOTIATE65,
    CODE_NEGOTIATE66,
    CODE_NEGOTIATE67,
    CODE_NEGOTIATE68,
    CODE_NEGOTIATE69,
    CODE_NEGOTIATE6A,
    CODE_NEGOTIATE6B,
    CODE_WAIT           = 0x70,
}ENUM_ANSI_REQUEST_CODE;

/*response type(ok or error)*/
typedef enum
{
    E_RESP_OK = 0,
    E_RESP_ERR,
    E_RESP_NONE,
}eAcseRespType;

/*
* ANSI protocol resp code:
* c12.18: CODE_OK ~ CODE_ISSS
* c12.22: CODE_OK ~ CODE_SGRR
*/
typedef enum{
    CODE_OK   = 0,  //No problems
    CODE_ERR  = 1,  //Rejection request. Reason not provided
    CODE_SNS  = 2,  //Service Not supported. Message is valid
    CODE_ISC  = 3,  //Insufficient Security clearance
    CODE_ONP  = 4,  //Operation not possible. Message is valid, but message could not support
    CODE_IAR  = 5,  //Inappropriate Action Request
    CODE_BSY  = 6,  //Device busy
    CODE_DNR  = 7,  //Data not ready
    CODE_DLK  = 8,  //Data Locked
    CODE_RNO  = 9,  //Renegotiate Request
    CODE_ISSS = 10, //Invalid service sequence state
    CODE_SME  = 11, //Security Mechanism Error
    CODE_UAT  = 12, //Unknown Application Title
    CODE_NETT = 13, //Network Time-out
    CODE_NETR = 14, //Network Not Reachable
    CODE_RQTL = 15, //Request Too Large
    CODE_RSTL = 16, //Response Too Large
    CODE_SGNP = 17, //Segmentation not possible
    CODE_SGRR = 18, //Segmentation error
}ENUM_ANSI_RESPONSE_CODE;

typedef union
{
    uint16 u16;
    struct
    {
        uint8  	ID_High:3;				//BIT8-10
        uint8  	STD_VS_MFG:1;		  	//BIT11   0=STD, 1=MFG
        uint8  	TAB_VS_PROC:1;			//BIT12   0=TAB, 1=PROC
        uint8  	Unrestricted_Read :1;   //BIT13
        uint8  	Unrestricted_Write:1;	//BIT14
        FILL	Filler:1;				//BIT15
        uint8  	ID_Low:8;				//BIT0-7
    }bits;
}TABLE_IDC_BFLD;

typedef union
{
	uint8 u8;
	struct
	{
		uint8 Group_permission0 :1;
		uint8 Group_permission1 :1;
		uint8 Group_permission2 :1;
		uint8 Group_permission3 :1;
		uint8 Group_permission4 :1;
		uint8 Group_permission5 :1;
		uint8 Group_permission6 :1;
		uint8 Group_permission7 :1;
	}bits;
}ACCESS_PERMISSION_BFLD;

typedef struct
{
    TABLE_IDC_BFLD 			Access_Table_Def;
    ACCESS_PERMISSION_BFLD 	Read;
    ACCESS_PERMISSION_BFLD 	Write;
}ACCESS_CONTROL_ENTRY_RCD;

#endif // ANSI_DEF_H
