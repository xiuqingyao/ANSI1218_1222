/*****************************************************************************
*                               Copyright(c)
*                            Hexing Electrical
*****************************************************************************/
/**
******************************************************************************
* @file     table00.c
* @brief    <b>table00</b>
* @author
* @date
* @details
******************************************************************************
* <center>History</center>
* @author
* @date
* @details
*****************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "table00.h"

/* Private constants ---------------------------------------------------------*/
const GEN_CONFIG_RCD GEN_CONFIG_TBL =
{
    #if 1
    .FORMAT_CONTROL_1 = (MODEL_SELECT_SRC_ST16<<4) | (CHAR_ORDER_ISO_7<<1) | DATA_ORDER_MSB,
    .FORMAT_CONTROL_2 = (INT_FORMAT_TWO<<6) | (ID_FORMAT_STRING<<5) | (DATA_ACCESS_METHOD_OFFSET<<3) | TM_FORMAT_UINT8,
    .FORMAT_CONTROL_3 = (NI_FORMAT_INT32<<4) | NI_FORMAT_INT32,
    "HEX ",     //DEVICE_CLASS
    .NAMEPLATE_TYPE = NAMEPLATE_TYPE_ELECTRIC,
    .DEFAULT_SET_USED =DEFAULT_SET_USED_NONE,
    .MAX_PROC_PARM_LENGTH = MAX_PROC_PARM_LENGTH_DEF,
    .MAX_RESP_DATA_LEN = MAX_RESP_DATA_LEN_DEF,
    .STD_VERSION_NO = STD_VERSION_NO_DEF,
    .STD_REVISION_NO = STD_REVISION_NO_DEF,
    .DIM_STD_TBLS_USED = DIM_STD_TBLS_USED_DEF,
    .DIM_MFG_TBLS_USED = DIM_MFG_TBLS_USED_DEF,
    .DIM_STD_PROC_USED = DIM_STD_PROC_USED_DEF,
    .DIM_MFG_PROC_USED = DIM_MFG_PROC_USED_DEF,
    .DIM_MFG_STATUS_USED = DIM_MFG_STATUS_USED_DEF,
    .NBR_PENDING = NBR_PENDING_DEF,
    {0}, //.STD_TBLS_USED[DIM_STD_TBLS_USED_DEF] = {},
    {0}, //.MFG_TBLS_USED[DIM_MFG_TBLS_USED_DEF] = {},
    {0}, //.STD_PROC_USED[DIM_STD_PROC_USED_DEF] = {},
    {0}, //.MFG_PROC_USED[DIM_MFG_PROC_USED_DEF] = {},
    {0}, //.STD_TBLS_WRITE[DIM_STD_TBLS_USED_DEF] = {},
    {0}, //.MFG_TBLS_WRITE[DIM_MFG_TBLS_USED_DEF] = {},
    #else
    {ST00_FORMAT_CONTROL_1_BFLD},
    {ST00_FORMAT_CONTROL_2_BFLD},
    {ST00_FORMAT_CONTROL_3_BFLD},
    {0x48, 0x58, 0x45, 0x20},       //"HXE "
    {ST00_NAMEPLATE_TYPE_ELECTRIC},
    {ST00_DEFAULT_SET_USED_NONE},
    {25},                           //ST07参数长
    {25},                           //ST08相应数据长
    {1},
    {0},
    {DIM_STD_TBLS_USED},            //7=最大ST表7*8-1=55
    {DIM_MFC_TBLS_USED},            //最大MT表7
    {DIM_STD_PROC_USED},            //最大标准进程号15
    {DIM_MFC_PROC_USED},            //最大厂家进程号23
    {DIM_MFC_STATUS_USED},         	//最大厂家定义状态数15
    {ZERO},                        	//不支持pengding
    //支持标准及自定义表格
    {N00+N01+N02+N03+N05+N06+N07,     N08+N11+N12+N13+N15, N16+N21+N22+N23, N24+N25+N26+N27+N28+N31, N32+N33, N41+N42+N43+N44, N51+N52+N53+N54+N55,N61+N62+N63,N64+N71,N72+N75+N76},//73 74Histroy log不支持
	{N00+N01+N02+N03+N04+N05+N06+N07, N08+N09+N11+N12},
    //支持标准过程及自定义过程
    {N03+N06+N07,                 N08+N09+N10,},
    {ZERO,                        ZERO,                    ZERO},
    //支持标准表写及标准进程写
    {N05+N06+N07,                 N13+N15,                 N22,                0,                             N33,     N42+N45,         N53+N54,    N61+N62,        0,   N73+N75},
    {N06+N07,                     N08+N09},
    #endif // 0
};

