/*****************************************************************************
*                               Copyright(c)
*                            Hexing Electrical
*****************************************************************************/
/**
******************************************************************************
* @file     table10.h
* @brief    Data Source Dimension Limits Table
* @author
* @date
* @details
******************************************************************************
* <center>History</center>
* @author
* @date
* @details
*****************************************************************************/

#ifndef TABLE10_H
#define TABLE10_H

/* Includes ------------------------------------------------------------------*/
#include "typedef.h"

typedef union
{
    uint8 value;
    struct
    {
        BOOL PF_EXCLUDE_FLAG:1;
        BOOL RESET_EXCLUDE_FLAG:1;
        BOOL BLOCK_DEMAND_FLAG:1;
        BOOL SLIDING_DEMAND_FLAG:1;
        BOOL THERMAL_DEMAND_FLAG:1;
        BOOL SET1_PRESENT_FLAG:1;
        BOOL SET2_PRESENT_FLAG:1;
        BOOL CONVERSION_ALG_FLAG:1;
    }bits;
}SOURCE_FLAGS_BFLD;

typedef struct
{
    SOURCE_FLAGS_BFLD SOURCE_FLAGS;
    uint8 NBR_UOM_ENTRIES;
    uint8 NBR_DEMAND_CTRL_ENTRIES;
    uint8 DATA_CTRL_LENGTH;
    uint8 NBR_DATA_CTRL_ENTRIES;
    uint8 NBR_CONSTANTS_ENTRIES;
    uint8 CONSTANTS_SELECTOR;
    uint8 NBR_SOURCES;
}SOURCE_RCD;

const SOURCE_RCD SOURCE_TBL;

#endif // TABLE10_H
