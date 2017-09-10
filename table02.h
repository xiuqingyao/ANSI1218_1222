/*****************************************************************************
*                               Copyright(c)
*                            Hexing Electrical
*****************************************************************************/
/**
******************************************************************************
* @file     table02.h
* @brief    <b>table02(Device Nameplate Table)</b>
* @author
* @date
* @details
******************************************************************************
* <center>History</center>
* @author
* @date
* @details
*****************************************************************************/
#ifndef TABLE02_H
#define TABLE02_H

/* Includes ------------------------------------------------------------------*/
#include "typedef.h"

/* Exported types ------------------------------------------------------------*/
/* Exported defines ----------------------------------------------------------*/
#define ST02_FREQ_50HZ               2
#define ST02_FREQ_50OR60HZ           3
#define ST02_FREQ_60HZ               4

#define ST02_E_NUM_ELEMENTS_ONE        1
#define ST02_E_NUM_ELEMENTS_TWO        2
#define ST02_E_NUM_ELEMENTS_TWO_HALF   3
#define ST02_E_NUM_ELEMENTS_THREE      4

#define ST02_E_BASE_TYPE_S_BASE        1
#define ST02_E_BASE_TYPE_A_BASE        2

#define ST02_E_ELEMENTS_VOLTS_120      3
#define ST02_E_ELEMENTS_VOLTS_208      4
#define ST02_E_ELEMENTS_VOLTS_240      5
#define ST02_E_ELEMENTS_VOLTS_277      6
#define ST02_E_ELEMENTS_VOLTS_480      7
#define ST02_E_ELEMENTS_VOLTS_120TO277 8
#define ST02_E_ELEMENTS_VOLTS_120TO480 9

#define ST02_E_ACCURACY_CLASS_RESERVED     0	  //default 0

/*configuration*/
//#if(CFG_METER_FROM == DFN_FROM_1S)
//#else
#if((CFG_PROJ_NO==DFN_PROJ_1475_1)||(CFG_FIRM_NO==DFN_PROJ_1475_2))
    #define CFG_METER_FREQ          ST02_FREQ_50HZ
    #define FREQUENCY               50                 // 50Hz
#else
    #define CFG_METER_FREQ          ST02_FREQ_60HZ
    #define FREQUENCY               60                 // 60Hz
#endif
#define CFG_METER_ELEMET        ST02_E_NUM_ELEMENTS_ONE
#define CFG_METER_BASE          ST02_E_BASE_TYPE_S_BASE
#define CFG_METER_MAX_AMP       "200A  "	  //6 char
#define CFG_METER_TEST_AMP      "30A   "	  //6 char
#define CFG_METER_VOLT_CLASS    ST02_E_ELEMENTS_VOLTS_240
#define CFG_METER_SUPPLY_VOLT   ST02_E_ELEMENTS_VOLTS_240


#define ST02_E_ELEMENTS_BFLD    ((CFG_METER_FREQ<<0)\
                                +(CFG_METER_ELEMET<<3)\
								+(CFG_METER_BASE<<6)\
								+(ST02_E_ACCURACY_CLASS_RESERVED<<10))


#define ST02_E_VOLTS_BFLD       ((CFG_METER_VOLT_CLASS<<0)\
                                +(CFG_METER_SUPPLY_VOLT<<4))
//#endif

typedef union
{
    uint16 u16;
    struct
    {
        uint16  Frequency:3;
        uint16  Number_of_elements:3;
        uint16  Base_type:4;
        uint16  Accuracy_class:6;
    }bits;
}E_ELEMENTS_BFLD;

typedef union
{
    uint8 u8;
    struct
    {
        uint8 Meter_element_voltage:4;
        uint8 Supply_voltage:4;
    }bits;
}E_VOLTS_BFLD;

typedef struct
{
    uint8 Maximum_amperage[6];
    uint8 Test_amperage[6];
}E_AMPS_RCD;

typedef struct
{
    uint8              Kh[6];
    uint8              Kt[6];
    uint8              Input_scalar;
    uint8              Configuration[5];
    E_ELEMENTS_BFLD    Elements;
    E_VOLTS_BFLD       Voltage;
    E_AMPS_RCD         Amperage;
}E_ELECTRIC_DEVICE_RCD;

const E_ELECTRIC_DEVICE_RCD DEV_NAMEPLATE_TBL;

#endif //TABLE02_H

