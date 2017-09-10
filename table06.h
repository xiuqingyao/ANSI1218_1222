/*****************************************************************************
*                               Copyright(c)
*                            Hexing Electrical
*****************************************************************************/
/**
******************************************************************************
* @file     table06.h
* @brief    Utility Information Table
* @author
* @date
* @details
******************************************************************************
* <center>History</center>
* @author
* @date
* @details
*****************************************************************************/
#ifndef TABLE06_H
#define TABLE06_H

/* Includes ------------------------------------------------------------------*/
#include "typedef.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
    uint8 OWNER_NAME[20];
    uint8 UTILITY_DIV[16];
    uint8 SERVICE_POINT_ID[20];
    uint8 ELEC_ADDR[20];
    uint8 DEVICE_ID[20];
    uint8 UTIL_SER_NO[20];
    uint8 CUSTOMER_ID[20];
    uint8 COORDINATE_1[10];
    uint8 COORDINATE_2[10];
    uint8 COORDINATE_3[10];
    uint8 TARIFF_ID[8];
    uint8 EX1_SW_VENDOR[4];
    uint8 EX1_SW_VERSION_NUMBER;
    uint8 EX1_SW_REVISION_NUMBER;
    uint8 EX2_SW_VENDOR[4];
    uint8 EX2_SW_VERSION_NUMBER;
    uint8 EX2_SW_REVISION_NUMBER;
    uint8 PROGRAMMER_NAME[10];
    uint8 MISC_ID[30];
    uint8 FW_LOAD_DATE[2];
}UTIL_INFO_RCD;

UTIL_INFO_RCD UTIL_INFO_TBL;

#endif // TABLE06_H

