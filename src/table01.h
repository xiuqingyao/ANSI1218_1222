/*****************************************************************************
*                               Copyright(c)
*                            Hexing Electrical
*****************************************************************************/
/**
******************************************************************************
* @file     table01.c
* @brief    <b>table01(General Manufacturer Identification Table)</b>
* @author
* @date
* @details
******************************************************************************
* <center>History</center>
* @author
* @date
* @details
*****************************************************************************/
#ifndef TABLE01_H
#define TABLE01_H

/* Includes ------------------------------------------------------------------*/
#include "typedef.h"
#include "ansi_tblmgr.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
    uint8 MANUFACTURER[4];
    uint8 ED_MODEL[8];
    uint8 HW_VERSION_NUMBER;
    uint8 HW_REVISION_NUMBER;
    uint8 FW_VERSION_NUMBER;
    uint8 FW_REVISION_NUMBER;
    uint8 MFG_SERIAL_NUMBER[16];
}MANUFACTURER_IDENT_RCD;

const MANUFACTURER_IDENT_RCD GENERAL_MFG_ID_TBL;

#endif /* TABLE01_H */

