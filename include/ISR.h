/*
─────────────────────── M5CP Salutron-Phantom-Detecter ────────────────────────

    This document contains confidential information and privileged material
    for the sole use of those authorized by True Fitness.  Any review, use,
    retention, distribution, or disclosure by anyone not authorized by True Fitness
    is strictly prohibited.  If you have a copy of this program/document
    and have not been authorized by True Fitness to possess it, please contact
    and return document(s) to True Fitness immediately.
    Copyright: True Fitness 2020-2021  All Rights Reserved.

───────────────────────────────────────────────────────────────────────────────

    Project:    M5CP Salutron-Phantom-Detecter
    Author:     Mark Doane
    Date:       12/30/20
    File:       ISR.h                 -Interrupt-Service-Routine header file.
    Software:   0121400               -Software number.
    Board:      M5Stick-C Plus        -Color Display, WiFi, Bluetooth, Three switchs, Red & Ir LEDs, IMU, PMU, RTC, Various I/O.
                                       will include an external 18650 Hat, and a proto Hat with the µSD data logger.  Interface
                                       to the Salutron will be through the "GROVE" header.

    Software Supplement: 0121800 REV-1.0.0.XLS.     (Yet to Be Created)
    
───────────────────────── REVISION RECORD ───────────────────────────
    
    ***** SEE 0121400-REV-X.X.X main.cpp FOR REVISION DETAILS *****

─────────────────────────────────────────────────────────────────────
*/

#ifndef     _ISR_h_
#define     _ISR_h_

#include    "Constants.h"                                                   // Include Gloabal constants.

//────────────────────────────── ISR VARIABLES ────────────────────────────────

    extern  volatile    uint32_t        UNIT_MODE;                          // Contains all UNIT control bits for various MODE's.
    extern  volatile    uint32_t        sPULSE_START_TME;                      // 32-Bit, Current micros START-TiME in µS.
    extern  volatile    uint32_t        sPULSE_STOP_TME;                       // 32-Bit, ELAPSED-TiME in µS.
    extern  volatile    uint32_t        sPULSE_ELAPSED_TME;                    // 32-Bit, ELAPSED-TiME in µS.
    extern  volatile    uint32_t        PRVS_PULSE_CNT;                      // PReVious-PULSE-CouNT.
    extern  volatile    uint32_t        CRNT_PULSE_CNT;                          // Current PULSE-CouNT.
    extern  volatile    _Bool           SAL_SIG_DET;                        // SALutron-SIGnal-DETect FLAG.
    
    extern  volatile    _Bool           LCD_BL_EN_FLAG;                     // LCD-Back-Light-ENable-FLAG.
    extern  volatile    _Bool           LED_EN_FLAG;                        // LED-ENable-FLAG.
    extern  volatile    _Bool           PWR_DSP_FLAG;                       // PoWeR-DiSPlay-screen-FLAG.
    extern  volatile    _Bool           SAL_DSP_FLAG;                       // SALutron-DiSPlay readout screen FLAG.    
    extern  volatile    _Bool           SYS_PWR_ON_FLAG;                    // SYStem-PoWeR-ON-FLAG.    
    extern  volatile    _Bool           DSP_SET_FLAG;
    extern  volatile    _Bool           PBTN_DET_FLAG;

    extern  volatile    uint8_t         LED_ON_TMR;                         // LED-ON-TiMeR, 1mS intervals.
    extern  volatile    uint16_t        LCD_ON_TMR;                         // LCD-ON-TiMeR, 1mS intervals.
    extern  volatile    uint16_t        DSP_MODE_TMR;                       // DiSPlay-MODE-TiMeR, 1mS intervals.
    extern  volatile    uint16_t        PBTN_DB_TMR;                        // Push-BuTtoN-De-Bouce-TiMeR, 1mS intervals.
    extern  volatile    uint16_t        SYS_PWR_ON_TMR;                     // SYStem-PoWeR-ON-TiMeR before sleep, 1mS intervals.    
    extern  volatile    uint8_t         SD_LOG_TMR;                         // 8-Bit 1mS OPEN-LOG-TiMeR.
    extern  volatile    uint8_t         sPULSE_HIGH_TME;                        // SALutron-sPulse SIGnal-TiMeR, 1mS intervals.
    extern  volatile    uint16_t        SYS_ACT_TMR;                        // SYStem-ACTivity-TiMeR, before sleep, 1mS intervals.    

    extern              I2C_AXP192      PMIC;    
    extern              M5Display       LCD;
    extern              portMUX_TYPE    GPIO_SYNC;
    extern              portMUX_TYPE    HW_TMR;

//────────────────────────────── ISR FUNCTIONS ────────────────────────────────

    extern  void IRAM_ATTR BTN_CHK_ISR(void);                               // CHecKs BuTtoN-Interrupt-Service-Routine.
    extern  void IRAM_ATTR SAL_CHK_ISR(void);                               // CHecKs SALutron-Interrupt-Service-Routine.
    extern  void IRAM_ATTR SYS_CHK_ISR(void);                               // CHecKs SYStem-Interrupt-Service-Routine.
    extern  void IRAM_ATTR TMR_CHK_ISR(void);                               // CHecKs TiMeR(s)-Interrupt-Service-Routine.

#endif