/*****************************************************************************
*                               Copyright(c)
*                            Hexing Electrical
*****************************************************************************/
/**
******************************************************************************
* @file     table12.c
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

/* Includes ------------------------------------------------------------------*/
#include "table12.h"

const UOM_ENTRY_RCD UOM_ENTRY_TBL =
{
    .forwadTotalEnergy          			= 0x00024000,
    .reverseTotalEnergy         			= 0x00018000,
    .absoluteActiveEnergy       			= 0x00030c00,
    .netActiveEnergy            			= 0x0007c000,
    .forwardActiveEnergy        			= 0x0000c001,
    .reverseActiveEnergy        			= 0x00030001,
    .Q1Power                    			= 0x00204001,
    .Q2Power                    			= 0x00208001,
    .Q3Power                    			= 0x00210001,
    .Q4Power                    			= 0x00220001,
    .phase1TotalPower           			= 0x00280200,
    .phase2TotalPower           			= 0x00300200,
    .phase3TotalPower           			= 0x00380200,
    .TotalActivePower           			= 0x00000200,
    .TotalReactivePower         			= 0x00000201,
    .TotalApparentPower         			= 0x00000202,
    .phase1Current              			= 0x00282a0c,
    .phase2Current              			= 0x00302a0c,
    .phase3Current              			= 0x00382a0c,
    .phase1Voltage              			= 0x00282a08,
    .phase2Voltage              			= 0x00302a08,
    .phase3Voltage              			= 0x00382a08,
    .powerFactor                			= 0x00003219,
    .phase1PowerFactor          			= 0x00283219,
    .phase2PowerFactor          			= 0x00303219,
    .phase3PowerFactor          			= 0x00383219,
    .networkFreqency            			= 0x00202a21,
    .phase1Angle                			= 0x00280216,
    .phase2Angle                			= 0x00300216,
    .phase3Angle                			= 0x00380216,
    .phase21Angle               			= 0x00080215,
    .phase31Angle               			= 0x00180215,
    .fowardActiveMaxDemand      			= 0x00024400,
    .reverseActiveMaxDemand     			= 0x00018400,
    .absoluteActiveMaxDemand    			= 0x0003c400,
    .networkActiveMaxDemand     			= 0x0007c400,
    .fowardReactiveMaxDemand    			= 0x0000c401,
    .reverseReactiveMaxDemand   			= 0x00030401,
    .Q1ReactiveMaxDemand        			= 0x00204401,
    .Q2ReactiveMaxDemand        			= 0x00208401,
    .Q3ReactiveMaxDemand        			= 0x00210401,
    .Q4ReactiveMaxDemand        			= 0x00220401,
    .temperature                			= 0x002002d9,
    .fowardActiveDemand         			= 0x00024300,
    .reverseActiveDemand        			= 0x00018300,
    .absoluteActiveDemand       			= 0x0003c300,
    .networkActiveDemand        			= 0x0007c300,
    .fowardReactiveDemand       			= 0x0000c301,
    .reverseReactiveDemand      			= 0x00030301,
    .Q1ReactiveDemand           			= 0x00204301,
    .Q2ReactiveDemand           			= 0x00208301,
    .Q3ReactiveDemand           			= 0x00210301,
    .Q4ReactiveDemand           			= 0x00220301,
    .forwadApparentDemand       			= 0x00024302,
    .reverseApparentDemand      			= 0x00018302,
    .forwadApparentEnergy          			= 0x00024002,
    .reverseApparentEnergy         			= 0x00018002,
    .forwardTotalNetCharge      			= 0x00024500,
    .reverseTotalNetCharge      			= 0x00018500,
    .forwardApparentNetCharge   			= 0x00024502,
    .reverseApparentNetCharge   			= 0x00018502,
    .phase1ReactiveTotalPower   			= 0x00280201,
    .phase2ReactiveTotalPower   			= 0x00300201,
    .phase3ReactiveTotalPower   			= 0x00380201,
    .phase1ApparentPower        			= 0x00280202,
    .phase2ApparentPower        			= 0x00300202,
    .phase3ApparentPower        			= 0x00380202,
    .fowardApparentMD           			= 0x00024402,
    .reverseApparentMD          			= 0x00018402,
    .absoluteApparentTotalActiveEnergy      = 0x0003C002,
    .absoluteApparentTotalReactiveEnergy    = 0x0003C001,
    .laggingReactivePower                   = 0x00014001,
    .capacitiveReactivePower                = 0x00028001,
    .laggingForwardReactivePower            = 0x0003C201,
    .laggingReverseReactivePower            = 0x0003C202,
    .laggingReactiveDemand                  = 0x00014401,
    .capacitiveReactiveDemand               = 0x00028401,
    .laggingForwardReactiveDemand           = 0x0003C401,
    .laggingReverseReactiveDemand           = 0x0003C402,
};


