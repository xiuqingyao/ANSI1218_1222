/*****************************************************************************
*                               Copyright(c)
*                            Hexing Electrical
*****************************************************************************/
/**
******************************************************************************
* @file     table12.h
* @brief    Units of Measure Entry Table
* @author
* @date
* @details
******************************************************************************
* <center>History</center>
* @author
* @date
* @details
*****************************************************************************/

#ifndef TABLE12_H
#define TABLE12_H

/* Includes ------------------------------------------------------------------*/
#include "typedef.h"

typedef union
{
    UINT32 uint32;
    struct
    {
        UINT32 Filler2:7;                   //bit24-31
        UINT32 Not_standard_defined:1;

        UINT32 Accountability_quadrant3:1;  //bit16-23
        UINT32 Accountability_quadrant4:1;
        UINT32 Net_flow:1;
        UINT32 Segmentation:3;
        UINT32 Harmonic:1;
        UINT32 Filler1:1;


        UINT32 Time_base:3;				   //bit8-15
        UINT32 Multiplier:3;
        UINT32 Accountability_quadrant1:1;
        UINT32 Accountability_quadrant2:1;

        UINT32 Unit_of_measure_code:8;       //bit0-7
    }bits;
}UOM_ENTRY_BFLD;

typedef struct
{
    UOM_ENTRY_BFLD forwadTotalEnergy;
    UOM_ENTRY_BFLD reverseTotalEnergy;
    UOM_ENTRY_BFLD absoluteActiveEnergy;
    UOM_ENTRY_BFLD netActiveEnergy;
    UOM_ENTRY_BFLD forwardActiveEnergy;
    UOM_ENTRY_BFLD reverseActiveEnergy;
    UOM_ENTRY_BFLD Q1Power;
    UOM_ENTRY_BFLD Q2Power;
    UOM_ENTRY_BFLD Q3Power;
    UOM_ENTRY_BFLD Q4Power;
    UOM_ENTRY_BFLD phase1TotalPower;
    UOM_ENTRY_BFLD phase2TotalPower;
    UOM_ENTRY_BFLD phase3TotalPower;
    UOM_ENTRY_BFLD TotalActivePower;
    UOM_ENTRY_BFLD TotalReactivePower;
    UOM_ENTRY_BFLD TotalApparentPower;
    UOM_ENTRY_BFLD phase1Current;
    UOM_ENTRY_BFLD phase2Current;
    UOM_ENTRY_BFLD phase3Current;
    UOM_ENTRY_BFLD phase1Voltage;
    UOM_ENTRY_BFLD phase2Voltage;
    UOM_ENTRY_BFLD phase3Voltage;
    UOM_ENTRY_BFLD powerFactor;
    UOM_ENTRY_BFLD phase1PowerFactor;
    UOM_ENTRY_BFLD phase2PowerFactor;
    UOM_ENTRY_BFLD phase3PowerFactor;
    UOM_ENTRY_BFLD networkFreqency;
    UOM_ENTRY_BFLD phase1Angle;
    UOM_ENTRY_BFLD phase2Angle;
    UOM_ENTRY_BFLD phase3Angle;
    UOM_ENTRY_BFLD phase21Angle;
    UOM_ENTRY_BFLD phase31Angle;
    UOM_ENTRY_BFLD fowardActiveMaxDemand;
    UOM_ENTRY_BFLD reverseActiveMaxDemand;
    UOM_ENTRY_BFLD absoluteActiveMaxDemand;
    UOM_ENTRY_BFLD networkActiveMaxDemand;
    UOM_ENTRY_BFLD fowardReactiveMaxDemand;
    UOM_ENTRY_BFLD reverseReactiveMaxDemand;
    UOM_ENTRY_BFLD Q1ReactiveMaxDemand;
    UOM_ENTRY_BFLD Q2ReactiveMaxDemand;
    UOM_ENTRY_BFLD Q3ReactiveMaxDemand;
    UOM_ENTRY_BFLD Q4ReactiveMaxDemand;
    UOM_ENTRY_BFLD temperature;
    UOM_ENTRY_BFLD fowardActiveDemand;
    UOM_ENTRY_BFLD reverseActiveDemand;
    UOM_ENTRY_BFLD absoluteActiveDemand;
    UOM_ENTRY_BFLD networkActiveDemand;
    UOM_ENTRY_BFLD fowardReactiveDemand;
    UOM_ENTRY_BFLD reverseReactiveDemand;
    UOM_ENTRY_BFLD Q1ReactiveDemand;
    UOM_ENTRY_BFLD Q2ReactiveDemand;
    UOM_ENTRY_BFLD Q3ReactiveDemand;
    UOM_ENTRY_BFLD Q4ReactiveDemand;
    UOM_ENTRY_BFLD forwadApparentDemand;
    UOM_ENTRY_BFLD reverseApparentDemand;
    UOM_ENTRY_BFLD forwadApparentEnergy;
    UOM_ENTRY_BFLD reverseApparentEnergy;
    UOM_ENTRY_BFLD forwardTotalNetCharge;
    UOM_ENTRY_BFLD reverseTotalNetCharge;
    UOM_ENTRY_BFLD forwardApparentNetCharge;
    UOM_ENTRY_BFLD reverseApparentNetCharge;
    UOM_ENTRY_BFLD phase1ReactiveTotalPower;
    UOM_ENTRY_BFLD phase2ReactiveTotalPower;
    UOM_ENTRY_BFLD phase3ReactiveTotalPower;
    UOM_ENTRY_BFLD phase1ApparentPower;
    UOM_ENTRY_BFLD phase2ApparentPower;
    UOM_ENTRY_BFLD phase3ApparentPower;
    UOM_ENTRY_BFLD fowardApparentMD;
    UOM_ENTRY_BFLD reverseApparentMD;
    UOM_ENTRY_BFLD absoluteApparentTotalActiveEnergy;
    UOM_ENTRY_BFLD absoluteApparentTotalReactiveEnergy;
    UOM_ENTRY_BFLD laggingReactivePower;
    UOM_ENTRY_BFLD capacitiveReactivePower;
    UOM_ENTRY_BFLD laggingForwardReactivePower;
    UOM_ENTRY_BFLD laggingReverseReactivePower;
    UOM_ENTRY_BFLD laggingReactiveDemand;
    UOM_ENTRY_BFLD capacitiveReactiveDemand;
    UOM_ENTRY_BFLD laggingForwardReactiveDemand;
    UOM_ENTRY_BFLD laggingReverseReactiveDemand;
}UOM_ENTRY_RCD;

const UOM_ENTRY_RCD UOM_ENTRY_TBL;

#endif // TABLE12_H
