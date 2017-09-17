/*****************************************************************************
*                               Copyright(c)
*                            Hexing Electrical
*****************************************************************************/
/**
******************************************************************************
* @file     table03.c
* @brief    <b>table03(End Device Mode Status Table)</b>
* @author
* @date
* @details
******************************************************************************
* <center>History</center>
* @author
* @date
* @details
*****************************************************************************/
#ifndef TABLE03_H
#define TABLE03_H

/* Includes ------------------------------------------------------------------*/
#include "typedef.h"
#include "table00.h"


/* Exported types ------------------------------------------------------------*/
typedef union
{
    uint8 value;
    struct
    {
        BOOL METERING_FLAG:1;
        BOOL TEST_MODE_FLAG:1;
        BOOL METER_SHOP_MODE_FLAG:1;
        BOOL FACTORY_FLAG:1;
        BOOL FILLER:4;
    }bits;
}ED_MODE_BFLD;

typedef union
{
    uint16 value;
    struct
    {
        BOOL UNPROGRAMMED_FLAG :1;
        BOOL CONFIGURATION_ERROR_FLAG :1;
        BOOL SELF_CHK_ERROR_FLAG :1;
        BOOL RAM_FAILURE_FLAG :1;
        BOOL ROM_FAILURE_FLAG :1;
        BOOL NONVOL_MEM_FAILURE_FLAG :1;
        BOOL CLOCK_ERROR_FLAG :1;
        BOOL MEASUREMENT_ERROR_FLAG :1;
        BOOL LOW_BATTERY_FLAG :1;
        BOOL LOW_LOSS_POTENTIAL_FLAG :1;
        BOOL DEMAND_OVERLOAD_FLAG :1;
        BOOL POWER_FAILURE_FLAG :1;
        BOOL TAMPER_DETECT_FLAG :1;
        BOOL REVERSE_ROTATION_FLAG :1;
        BOOL FILLER :2;
    }bits;
}ED_STD_STATUS1_BFLD;

typedef union
{
    uint8 value;
    struct
    {
        BOOL FILLER:8;
    }bits;
}ED_STD_STATUS2_BFLD;

typedef union
{
    uint8 value;
    struct
    {
        BOOL phaseInversion:1;       //Phase inversion(逆相序)
	    BOOL commsFail:1;			  //communications error (overflow, busy, invalid command length
	    BOOL invalidPassword:1;      //wrong password for the given port was used
	    BOOL magnetDetect:1;          //检测到外磁场    1=检测到外磁场
	    BOOL relayFraud:1;           //继电器欺诈检测  1=发生欺诈
	    BOOL realyState:1;           //继电器状态      1=close  0=open
        BOOL coverState:1;           //开内罩          1=打开 0=关闭
        BOOL caseState:1;            //开外罩          1=打开 0=关闭
    }bits;
}ED_MFG_STATUS_RCD;

typedef struct
{
    ED_MODE_BFLD ED_MODE;
    ED_STD_STATUS1_BFLD ED_STD_STATUS1;
    ED_STD_STATUS2_BFLD ED_STD_STATUS2;
    ED_MFG_STATUS_RCD ED_MFG_STATUS;
}ED_MODE_STATUS_RCD;

ED_MODE_STATUS_RCD END_DEV_MODE_STATUS_TBL;

#endif /* TABLE03_H */
