#ifndef ANSI_C1219_H
#define ANSI_C1219_H

#include "ansi_tbldef.h"
#include "table00.h"
#include "table01.h"
#include "table02.h"
#include "table03.h"
#include "table05.h"
#include "table06.h"
#include "table10.h"
#include "table11.h"
#include "table12.h"

/********************************************************************************
                     ANSI table configuration
*********************************************************************************/
/***********************************************
   table0(General Configuration) configuration
************************************************/
const STRU_COMTABL STRU_ST00[]=
{
    /*item addr, item size, sub_item number, operation_mode*/
    {(uint8*)&GEN_CONFIG_TBL.FORMAT_CONTROL_1,      1,                     1,   OPMOD_R},
    {(uint8*)&GEN_CONFIG_TBL.FORMAT_CONTROL_2,      1,                     1,   OPMOD_R},
    {(uint8*)&GEN_CONFIG_TBL.FORMAT_CONTROL_3,      1,                     1,   OPMOD_R},
    {(uint8*)GEN_CONFIG_TBL.DEVICE_CLASS,	        4,                     1,   OPMOD_R},
    {(uint8*)&GEN_CONFIG_TBL.NAMEPLATE_TYPE,		1,                     1,   OPMOD_R},
    {(uint8*)&GEN_CONFIG_TBL.DEFAULT_SET_USED,	    1,                     1,   OPMOD_R},
    {(uint8*)&GEN_CONFIG_TBL.MAX_PROC_PARM_LENGTH,  1,                     1,   OPMOD_R},
    {(uint8*)&GEN_CONFIG_TBL.MAX_RESP_DATA_LEN,	    1,                     1,   OPMOD_R},
    {(uint8*)&GEN_CONFIG_TBL.STD_VERSION_NO,	    1,                     1,   OPMOD_R},
    {(uint8*)&GEN_CONFIG_TBL.STD_REVISION_NO,	    1,                     1,   OPMOD_R},
    {(uint8*)&GEN_CONFIG_TBL.DIM_STD_TBLS_USED,	    1,                     1,   OPMOD_R},
    {(uint8*)&GEN_CONFIG_TBL.DIM_MFG_TBLS_USED,	    1,                     1,   OPMOD_R},
    {(uint8*)&GEN_CONFIG_TBL.DIM_STD_PROC_USED,	    1,                     1,   OPMOD_R},
    {(uint8*)&GEN_CONFIG_TBL.DIM_MFG_PROC_USED,	    1,                     1,   OPMOD_R},
    {(uint8*)&GEN_CONFIG_TBL.DIM_MFG_STATUS_USED,   1,                     1,   OPMOD_R},
    {(uint8*)&GEN_CONFIG_TBL.NBR_PENDING,		    1,                     1,   OPMOD_R},
    {(uint8*)GEN_CONFIG_TBL.STD_TBLS_USED,		    DIM_STD_TBLS_USED_DEF, 1,   OPMOD_R},
    {(uint8*)GEN_CONFIG_TBL.MFG_TBLS_USED,		    DIM_MFG_TBLS_USED_DEF, 1,   OPMOD_R},
    {(uint8*)GEN_CONFIG_TBL.STD_PROC_USED,		    DIM_STD_PROC_USED_DEF, 1,   OPMOD_R},
    {(uint8*)GEN_CONFIG_TBL.MFG_PROC_USED,		    DIM_MFG_PROC_USED_DEF, 1,   OPMOD_R},
    {(uint8*)GEN_CONFIG_TBL.STD_TBLS_WRITE,		    DIM_STD_TBLS_USED_DEF, 1,   OPMOD_R},
    {(uint8*)GEN_CONFIG_TBL.MFG_TBLS_WRITE,		    DIM_MFG_TBLS_USED_DEF, 1,   OPMOD_R},
};
#define  ST00_ITEM   (sizeof(STRU_ST00) / sizeof(STRU_COMTABL))
#define  ST00_SIZE   (sizeof(GEN_CONFIG_RCD))

/***************************************************************
    table1(General Manufacturer Identification) configuration
****************************************************************/
const STRU_COMTABL STRU_ST01[] =
{
    {(uint8*)GENERAL_MFG_ID_TBL.MANUFACTURER,			4,  1,   OPMOD_R},
    {(uint8*)GENERAL_MFG_ID_TBL.ED_MODEL,				8,  1,   OPMOD_R},
    {(uint8*)&GENERAL_MFG_ID_TBL.HW_VERSION_NUMBER,		1,  1,   OPMOD_R},
    {(uint8*)&GENERAL_MFG_ID_TBL.HW_REVISION_NUMBER,	1,  1,   OPMOD_R},
    {(uint8*)&GENERAL_MFG_ID_TBL.FW_VERSION_NUMBER,		1,  1,   OPMOD_R},
    {(uint8*)&GENERAL_MFG_ID_TBL.FW_REVISION_NUMBER,	1,  1,   OPMOD_R},
    {(uint8*)GENERAL_MFG_ID_TBL.MFG_SERIAL_NUMBER,      16, 1,   OPMOD_R},
};
#define  ST01_ITEM   (sizeof(STRU_ST01) / sizeof(STRU_COMTABL))
#define  ST01_SIZE   (sizeof(MANUFACTURER_IDENT_RCD))

/***********************************************
   table2(Device Nameplate) configuration
************************************************/
const STRU_COMTABL STRU_ST02[] =
{
    {(uint8*)DEV_NAMEPLATE_TBL.Kh,			                    6,  1,   OPMOD_R},
    {(uint8*)DEV_NAMEPLATE_TBL.Kt,			                    6,  1,   OPMOD_R},
    {(uint8*)&DEV_NAMEPLATE_TBL.Input_scalar,	                1,  1,   OPMOD_R},
    {(uint8*)DEV_NAMEPLATE_TBL.Configuration,	                5,  1,   OPMOD_R},
    {(uint8*)&DEV_NAMEPLATE_TBL.Elements,		                2,  1,   OPMOD_R},
    {(uint8*)&DEV_NAMEPLATE_TBL.Voltage,		                1,  1,   OPMOD_R},
    {(uint8*)DEV_NAMEPLATE_TBL.Amperage.Maximum_amperage,       12, 1,   OPMOD_R},
};
#define  ST02_ITEM   (sizeof(STRU_ST02) / sizeof(STRU_COMTABL))
#define  ST02_SIZE   (sizeof(E_ELECTRIC_DEVICE_RCD))

/***********************************************
   table3(End Device Mode Status) configuration
************************************************/
const STRU_COMTABL STRU_ST03[] =
{
    {(uint8*)&END_DEV_MODE_STATUS_TBL.ED_MODE,			1,  1,   OPMOD_R},
    {(uint8*)&END_DEV_MODE_STATUS_TBL.ED_STD_STATUS1,	2,  1,   OPMOD_R},
    {(uint8*)&END_DEV_MODE_STATUS_TBL.ED_STD_STATUS2,	1,  1,   OPMOD_R},
    {(uint8*)&END_DEV_MODE_STATUS_TBL.ED_MFG_STATUS,	1,  1,   OPMOD_R},
};
#define  ST03_ITEM   (sizeof(STRU_ST03) / sizeof(STRU_COMTABL))
#define  ST03_SIZE   (sizeof(ED_MODE_STATUS_RCD))

/***************************************************
    table5(Device Identification) configuration
****************************************************/
STRU_COMTABL STRU_ST05[] =
{
    {DEVICE_IDENTIFICATION_TBL.IDENTIFICATION, 20, 1, OPMOD_W + OPMOD_R},
};
#define  ST05_ITEM   (sizeof(STRU_ST05) / sizeof(STRU_COMTABL))
#define  ST05_SIZE   (sizeof(IDENT_RCD))

/***************************************************
    table6(Utility Information Table) configuration
****************************************************/
STRU_COMTABL STRU_ST06[] =
{
    {UTIL_INFO_TBL.OWNER_NAME,                 20, 1, OPMOD_W + OPMOD_R},//所有者姓名
    {UTIL_INFO_TBL.UTILITY_DIV,                16, 1, OPMOD_W + OPMOD_R},//事业局部门
    {UTIL_INFO_TBL.SERVICE_POINT_ID,           20, 1, OPMOD_W + OPMOD_R},//服务点
    {UTIL_INFO_TBL.ELEC_ADDR,                  20, 1, OPMOD_W + OPMOD_R},//联系地址
    {UTIL_INFO_TBL.DEVICE_ID,                  20, 1, OPMOD_W + OPMOD_R},//设备ID
    {UTIL_INFO_TBL.UTIL_SER_NO,                20, 1, OPMOD_W + OPMOD_R},//事业单位序号
    {UTIL_INFO_TBL.CUSTOMER_ID,                20, 1, OPMOD_W + OPMOD_R},//用户ID
    {UTIL_INFO_TBL.COORDINATE_1,               10, 1, OPMOD_W + OPMOD_R},//坐标X
    {UTIL_INFO_TBL.COORDINATE_2,               10, 1, OPMOD_W + OPMOD_R},//坐标Y
    {UTIL_INFO_TBL.COORDINATE_3,               10, 1, OPMOD_W + OPMOD_R},//坐标Z
    {UTIL_INFO_TBL.TARIFF_ID,                  8,  1, OPMOD_W + OPMOD_R},//费率号
    {UTIL_INFO_TBL.EX1_SW_VENDOR,              4,  1, OPMOD_W + OPMOD_R},//软件贩售商1
    {&UTIL_INFO_TBL.EX1_SW_VERSION_NUMBER,     1,  1, OPMOD_W + OPMOD_R},//软件版本号1
    {&UTIL_INFO_TBL.EX1_SW_REVISION_NUMBER,    1,  1, OPMOD_W + OPMOD_R},//软件修订号1
    {UTIL_INFO_TBL.EX2_SW_VENDOR,              4,  1, OPMOD_W + OPMOD_R},//软件贩售商2
    {&UTIL_INFO_TBL.EX2_SW_VERSION_NUMBER,     1,  1, OPMOD_W + OPMOD_R},//软件版本号2
    {&UTIL_INFO_TBL.EX2_SW_REVISION_NUMBER,    1,  1, OPMOD_W + OPMOD_R},//软件修订号2
    {UTIL_INFO_TBL.PROGRAMMER_NAME,            10, 1, OPMOD_W + OPMOD_R},//上一次编程员或编程设备的名字
    {UTIL_INFO_TBL.MISC_ID,                    30, 1, OPMOD_W + OPMOD_R},//其他关联的ID号
    {UTIL_INFO_TBL.FW_LOAD_DATE,               3,  1, OPMOD_W + OPMOD_R},//固件下装日期
};
#define  ST06_ITEM   (sizeof(STRU_ST06) / sizeof(STRU_COMTABL))
#define  ST06_SIZE   (sizeof(UTIL_INFO_TBL))

/****************************************************************
    table10(Data Source Dimension Limits Table) configuration
*****************************************************************/
const STRU_COMTABL STRU_ST10[] =
{
    {(uint8*)&SOURCE_TBL.SOURCE_FLAGS,              1, 1, OPMOD_R},
    {(uint8*)&SOURCE_TBL.NBR_UOM_ENTRIES,           1, 1, OPMOD_R},//计量元素的最大个数
    {(uint8*)&SOURCE_TBL.NBR_DEMAND_CTRL_ENTRIES,   1, 1, OPMOD_R},//需量类元素的最大个数
    {(uint8*)&SOURCE_TBL.DATA_CTRL_LENGTH,          1, 1, OPMOD_R},//控制类元素ID长度
    {(uint8*)&SOURCE_TBL.NBR_DATA_CTRL_ENTRIES,     1, 1, OPMOD_R},//控制类元素的最大个数
    {(uint8*)&SOURCE_TBL.NBR_CONSTANTS_ENTRIES,     1, 1, OPMOD_R},//常数类元素的最大个数
    {(uint8*)&SOURCE_TBL.CONSTANTS_SELECTOR,        1, 1, OPMOD_R},//常数种类选择
    {(uint8*)&SOURCE_TBL.NBR_SOURCES,               1, 1, OPMOD_R},//所有元素的最多个数
};
#define  ST10_ITEM   (sizeof(STRU_ST10) / sizeof(STRU_COMTABL))
#define  ST10_SIZE   (sizeof(SOURCE_RCD))

/****************************************************************
    table11(Actual Data Sources Limiting Table) configuration
*****************************************************************/
STRU_COMTABL STRU_ST11[] =
{
    {(uint8*)&ACTUAL_SOURCE_TBL.SOURCE_FLAGS,              1, 1, OPMOD_W + OPMOD_R},
    {(uint8*)&ACTUAL_SOURCE_TBL.NBR_UOM_ENTRIES,           1, 1, OPMOD_W + OPMOD_R},
    {(uint8*)&ACTUAL_SOURCE_TBL.NBR_DEMAND_CTRL_ENTRIES,   1, 1, OPMOD_W + OPMOD_R},
    {(uint8*)&ACTUAL_SOURCE_TBL.DATA_CTRL_LENGTH,          1, 1, OPMOD_W + OPMOD_R},
    {(uint8*)&ACTUAL_SOURCE_TBL.NBR_DATA_CTRL_ENTRIES,     1, 1, OPMOD_W + OPMOD_R},
    {(uint8*)&ACTUAL_SOURCE_TBL.NBR_CONSTANTS_ENTRIES,     1, 1, OPMOD_W + OPMOD_R},
    {(uint8*)&ACTUAL_SOURCE_TBL.CONSTANTS_SELECTOR,        1, 1, OPMOD_W + OPMOD_R},
    {(uint8*)&ACTUAL_SOURCE_TBL.NBR_SOURCES,               1, 1, OPMOD_W + OPMOD_R},
};
#define  ST11_ITEM   (sizeof(STRU_ST11) / sizeof(STRU_COMTABL))
#define  ST11_SIZE   (sizeof(SOURCE_RCD))

/****************************************************************
    table12(Units of Measure Entry Table) configuration
*****************************************************************/
const STRU_COMTABL STRU_ST12[] =
{
    {(uint8*)&UOM_ENTRY_TBL.forwadTotalEnergy          			    , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.reverseTotalEnergy         		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.absoluteActiveEnergy       		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.netActiveEnergy            		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.forwardActiveEnergy        		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.reverseActiveEnergy        		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.Q1Power                    		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.Q2Power                    		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.Q3Power                    		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.Q4Power                    		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.phase1TotalPower           		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.phase2TotalPower           		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.phase3TotalPower           		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.TotalActivePower           		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.TotalReactivePower         		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.TotalApparentPower         		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.phase1Current              		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.phase2Current              		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.phase3Current              		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.phase1Voltage              		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.phase2Voltage              		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.phase3Voltage              		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.powerFactor                		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.phase1PowerFactor          		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.phase2PowerFactor          		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.phase3PowerFactor          		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.networkFreqency            		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.phase1Angle                		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.phase2Angle                		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.phase3Angle                		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.phase21Angle               		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.phase31Angle               		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.fowardActiveMaxDemand      		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.reverseActiveMaxDemand     		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.absoluteActiveMaxDemand    		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.networkActiveMaxDemand     		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.fowardReactiveMaxDemand    		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.reverseReactiveMaxDemand   		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.Q1ReactiveMaxDemand        		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.Q2ReactiveMaxDemand        		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.Q3ReactiveMaxDemand        		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.Q4ReactiveMaxDemand        		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.temperature                		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.fowardActiveDemand         		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.reverseActiveDemand        		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.absoluteActiveDemand       		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.networkActiveDemand        		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.fowardReactiveDemand       		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.reverseReactiveDemand      		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.Q1ReactiveDemand           		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.Q2ReactiveDemand           		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.Q3ReactiveDemand           		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.Q4ReactiveDemand           		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.forwadApparentDemand       		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.reverseApparentDemand      		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.forwadTotalEnergy          		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.reverseTotalEnergy         		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.forwardTotalNetCharge      		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.reverseTotalNetCharge      		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.forwardApparentNetCharge   		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.reverseApparentNetCharge   		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.phase1ReactiveTotalPower   		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.phase2ReactiveTotalPower   		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.phase3ReactiveTotalPower   		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.phase1ApparentPower        		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.phase2ApparentPower        		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.phase3ApparentPower        		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.fowardApparentMD           		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.reverseApparentMD          		        , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.absoluteApparentTotalActiveEnergy       , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.absoluteApparentTotalReactiveEnergy     , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.laggingReactivePower                    , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.capacitiveReactivePower                 , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.laggingForwardReactivePower             , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.laggingReverseReactivePower             , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.laggingReactiveDemand                   , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.capacitiveReactiveDemand                , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.laggingForwardReactiveDemand            , 4, 1, OPMOD_R},
    {(uint8*)&UOM_ENTRY_TBL.laggingReverseReactiveDemand   			, 4, 1, OPMOD_R},
};
#define  ST12_ITEM   (sizeof(STRU_ST12) / sizeof(STRU_COMTABL))
#define  ST12_SIZE   (sizeof(UOM_ENTRY_RCD))

/********************************************************************************
                    ANSI C12.19 table for protocol read/write
*********************************************************************************/
const STRU_INDEX_TABLE C1219_TABLE[] =
{
    /*table_index, table_address, table_items, table_size, table_access_right*/
    {ST00,	(STRU_COMTABL*)STRU_ST00,	ST00_ITEM,	ST00_SIZE,	(TB_OPMOD_READ_ACCESS)},
    {ST01,	(STRU_COMTABL*)STRU_ST01,	ST01_ITEM,	ST01_SIZE,	(TB_OPMOD_READ_ACCESS)},
    {ST02,	(STRU_COMTABL*)STRU_ST02,	ST02_ITEM,	ST02_SIZE,	(TB_OPMOD_READ_ACCESS)},
    {ST03,	(STRU_COMTABL*)STRU_ST03,	ST03_ITEM,	ST03_SIZE,	(TB_OPMOD_READ_ACCESS)},
    {ST05,	(STRU_COMTABL*)STRU_ST05,	ST05_ITEM,	ST05_SIZE,	(TB_OPMOD_READ_ACCESS + TB_OPMOD_WRITE_ACCESS)},
    {ST06,	(STRU_COMTABL*)STRU_ST06,	ST06_ITEM,	ST06_SIZE,	(TB_OPMOD_READ_ACCESS + TB_OPMOD_WRITE_ACCESS)},
    {ST10,	(STRU_COMTABL*)STRU_ST10,	ST10_ITEM,	ST10_SIZE,	(TB_OPMOD_READ_ACCESS)},
    {ST11,	(STRU_COMTABL*)STRU_ST11,	ST11_ITEM,	ST11_SIZE,	(TB_OPMOD_READ_ACCESS + TB_OPMOD_WRITE_ACCESS)},
    {ST12,	(STRU_COMTABL*)STRU_ST12,	ST12_ITEM,	ST12_SIZE,	(TB_OPMOD_READ_ACCESS)},
};
const uint16 g_AnsiTabSize = sizeof(C1219_TABLE)/sizeof(STRU_INDEX_TABLE);

#endif // ANSI_C1219_H
