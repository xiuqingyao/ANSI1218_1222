/*****************************************************************************
*                               Copyright(c)
*                            Hexing Electrical
*****************************************************************************/
/**
******************************************************************************
* @file     table05.c
* @brief    Device Identification Table
* @author
* @date
* @details
******************************************************************************
* <center>History</center>
* @author
* @date
* @details
*****************************************************************************/
#ifndef TABLE05_H
#define TABLE05_H

/* Includes ------------------------------------------------------------------*/
#include "typedef.h"
#include "ansi_tblmgr.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
    uint8 IDENTIFICATION[20];
}IDENT_RCD;

IDENT_RCD DEVICE_IDENTIFICATION_TBL;

#endif /* TABLE05_H */

