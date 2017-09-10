/*****************************************************************************
*                               Copyright(c)
*                            Hexing Electrical
*****************************************************************************/
/**
******************************************************************************
* @file     table00.h
* @brief    <b>table00(General Configuration Table)</b>
* @author
* @date
* @details
******************************************************************************
* <center>History</center>
* @author
* @date
* @details
*****************************************************************************/
#ifndef TABLE00_H
#define TABLE00_H

/* Includes ------------------------------------------------------------------*/
#include "typedef.h"
#include "ansi_tblmgr.h"

/* Exported types ------------------------------------------------------------*/
#define MAX_PROC_PARM_LENGTH_DEF    25
#define MAX_RESP_DATA_LEN_DEF       25
#define STD_VERSION_NO_DEF          2
#define STD_REVISION_NO_DEF         0
#define DIM_STD_TBLS_USED_DEF 		10
#define DIM_MFG_TBLS_USED_DEF		2
#define DIM_STD_PROC_USED_DEF		2
#define DIM_MFG_PROC_USED_DEF		3
#define DIM_MFG_STATUS_USED_DEF		1
#define NBR_PENDING_DEF		        0

//FORMAT_CONTROL_1_BFLD
typedef enum
{
    DATA_ORDER_LSB=0,
    DATA_ORDER_MSB,
}DATA_ORDER_ENUM;

typedef enum
{
    CHAR_FORMAT_RESERVED=0,
    CHAR_ORDER_ISO_7,
    CHAR_ORDER_ISO_8859,
}CHAR_FORMAT_ENUM;

typedef enum
{
    MODEL_SELECT_SRC_ST16=0,
    MODEL_SELECT_DECADE10,
}MODEL_SELECT_ENUM;

//FORMAT_CONTROL_2_BFLD
typedef enum
{
    TM_FORMAT_NONE=0,
    TM_FORMAT_BCD,
    TM_FORMAT_UINT8,
    TM_FORMAT_UINT32_MIN,
    TM_FORMAT_UINT32_SEC,
}TM_FORMAT_ENUM;        //时间表现格式

typedef enum
{
    DATA_ACCESS_METHOD_ONLY=0,
    DATA_ACCESS_METHOD_OFFSET,
    DATA_ACCESS_METHOD_INDEX,
    DATA_ACCESS_METHOD_BOTH,
}DATA_ACCESS_METHOD_ENUM;        //数据访问方式

typedef enum
{
    ID_FORMAT_STRING=0,
    ID_FORMAT_BCD,
}ID_FORMAT_ENUM;        //ID类的表达格式

typedef enum
{
    INT_FORMAT_TWO=0,
    INT_FORMAT_ONES,
    INT_FORMAT_SIGNED,
    INT_FORMAT_RESERVED,
}INT_FORMAT_ENUM;        //有符号整型数据的格式

//FORMAT_CONTROL_3_BFLD
typedef enum
{
    NI_FORMAT_FLOAT64=0,
    NI_FORMAT_FLOAT32,
    NI_FORMAT_FLOAT_CHAR12,
    NI_FORMAT_FLOAT_CHAR6,
    NI_FORMAT_INT32_POINT4,
    NI_FORMAT_FIXED_BCD6,
    NI_FORMAT_FIXED_BCD4,
    NI_FORMAT_INT24,
    NI_FORMAT_INT32,
    NI_FORMAT_INT40,
    NI_FORMAT_INT48,
    NI_FORMAT_INT64,
    NI_FORMAT_FIXED_BCD8,
    NI_FORMAT_FLOAT_CHAR21,
}NI_FORMAT_ENUM;        //无符号整型数据类型的格式

typedef NI_FORMAT_ENUM NI_FORMAT1_ENUM;        //无符号整型数据类型NI_FMAT1的格式
typedef NI_FORMAT_ENUM NI_FORMAT2_ENUM;        //无符号整型数据类型NI_FMAT2的格式

//NAMEPLATE_TYPE
typedef enum
{
    NAMEPLATE_TYPE_GAS=0,
    NAMEPLATE_TYPE_WATER,
    NAMEPLATE_TYPE_ELECTRIC,
}NAMEPLATE_TYPE_ENUM;        //设备类型

//DEFAULT_SET_USED
typedef enum
{
    DEFAULT_SET_USED_NONE=0,
    DEFAULT_SET_USED_SIMPLE,
    DEFAULT_SET_USED_DEMAND,
    DEFAULT_SET_USED_TOU,
    DEFAULT_SET_USED_PROFILE,
}DEFAULT_SET_USED_ENUM;        //标准中的默认Table配置集使用类型

//table00 declare
typedef union
{
    uint8 value;
    struct
    {
        BOOL DATA_ORDER:1;
        BOOL CHAR_FORMAT:3;
        BOOL MODEL_SELECT:3;
        BOOL FILLER:1;
    }bits;
}FORMAT_CONTROL_1_BFLD;

typedef union
{
    uint8 value;
    struct

    {
        BOOL TM_FORMAT:3;
        BOOL DATA_ACCESS_METHOD:2;
        BOOL ID_FORM:1;
        BOOL INT_FORMAT:2;
    }bits;
}FORMAT_CONTROL_2_BFLD;

typedef union
{
    uint8 value;
    struct
    {
        BOOL NI_FORMAT1:4;
        BOOL NI_FORMAT2:4;
    }bits;
}FORMAT_CONTROL_3_BFLD;

typedef struct
{
    FORMAT_CONTROL_1_BFLD FORMAT_CONTROL_1; //格式类型1
    FORMAT_CONTROL_2_BFLD FORMAT_CONTROL_2; //格式类型2
    FORMAT_CONTROL_3_BFLD FORMAT_CONTROL_3; //格式类型3
    ARRAY DEVICE_CLASS[4];              //厂商标识
    uint8 NAMEPLATE_TYPE;               //设备类型
    uint8 DEFAULT_SET_USED;             //标准中的默认Table配置集使用类型
    uint8 MAX_PROC_PARM_LENGTH;         //执行所带参数最大值
    uint8 MAX_RESP_DATA_LEN;            //响应所带参数最大值
    uint8 STD_VERSION_NO;               //C12.19的版本
    uint8 STD_REVISION_NO;              //C12.19的修订号
    uint8 DIM_STD_TBLS_USED;            //能表达表计中实现的标准table的最少字节数
    uint8 DIM_MFG_TBLS_USED;            //能表达表计中实现的厂家定义table的最少字节数
    uint8 DIM_STD_PROC_USED;            //能表达表计中实现的标准过程的最少字节数
    uint8 DIM_MFG_PROC_USED;            //能表达表计中实现的厂家定义过程的最少字节数
    uint8 DIM_MFG_STATUS_USED;          //能表达表计中实现的厂家自定义状态标志的最少字节数
    uint8 NBR_PENDING;                  //Pending状态集个数
    uint8 STD_TBLS_USED[DIM_STD_TBLS_USED_DEF];	//表中实现标准table的实际情况
    uint8 MFG_TBLS_USED[DIM_MFG_TBLS_USED_DEF];  //表中实现厂家定义table的实际情况
    uint8 STD_PROC_USED[DIM_STD_PROC_USED_DEF];  //表中能支持的标准过程的实际情况
    uint8 MFG_PROC_USED[DIM_MFG_PROC_USED_DEF];  //表中能支持的厂家自定义过程的实际情况
    uint8 STD_TBLS_WRITE[DIM_STD_TBLS_USED_DEF]; //表中实现的标准table是否可写的实际情况
    uint8 MFG_TBLS_WRITE[DIM_MFG_TBLS_USED_DEF]; //表中实现的厂家定义table是否可写的实际情况
}GEN_CONFIG_RCD;

const GEN_CONFIG_RCD GEN_CONFIG_TBL;

#endif //TABLE00_H
