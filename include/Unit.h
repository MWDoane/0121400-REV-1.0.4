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
    File:       Unit.h                -Header files needed for Salutron-Phantom-Detecter.
    Software:   0121400               -Software number.
    Board:      M5Stick-C Plus        -Color Display, WiFi, Bluetooth, Three switchs, Red & Ir LEDs, IMU, PMU, RTC, Various I/O.
                                       will include an external 18650 Hat, and a proto Hat with the µSD data logger.  Interface
                                       to the Salutron will be through the "GROVE" header.

    Software Supplement: 0121800 REV-1.0.0.XLS.     (Yet to Be Created)
    
───────────────────────── REVISION RECORD ───────────────────────────
    
    ***** SEE 0121400-REV-X.X.X main.cpp FOR REVISION DETAILS *****

─────────────────────────────────────────────────────────────────────
*/    

#ifndef     _Unit_h_
#define     _Unit_

#include    "Constants.h"                                                   // Include Gloabal constants.


//──────────────────────────── DEVICE VARIABLES ───────────────────────────────

extern  volatile    uint32_t            UNIT_MODE;                          // Contains all UNIT control bits for various MODE's.
extern  volatile    uint16_t            UNIT_TMRS[10];                      // Contains all UNIT TiMeRS for all timing requirements.

extern  RTC_DATA_ATTR   uint32_t        DS_CRNT_PULSE_CNT;
extern  RTC_DATA_ATTR   uint32_t        DS_PRVS_PULSE_CNT;
extern  RTC_DATA_ATTR   uint8_t         DS_OP_MODE;

extern              float               HR_Value;                           // Calculated Heart-Rate.
extern  volatile    uint32_t            PRVS_PULSE_CNT;                     // PReVious-PULSE-CouNT.
extern  volatile    uint32_t            CRNT_PULSE_CNT;                     // Accumulated PULSE-CouNT.
extern  volatile    uint32_t            sPULSE_ELAPSED_TME;                 // 32-Bit, ELAPSED-TiME in µS.
extern  volatile    uint16_t            SYS_ACT_TMR;                        // SYStem-ACTivity-TiMeR, before sleep, 1mS intervals.    
extern  volatile    uint16_t            LCD_ON_TMR;                         // LCD-DiSPlay-TiMeR, 1mS intervals.
extern              uint8_t             PrevSecond;                         // Previous Second byte.
extern              uint8_t             PrevDay;                            // Previous Day byte.
extern  volatile    _Bool               LCD_BL_EN_FLAG;                     // LCD-Back-Light-ENable-FLAG.
extern  volatile    _Bool               LED_EN_FLAG;                        // LED-ENable-FLAG.
extern              _Bool               GPIO_WAKE_UP_FLAG;
extern              _Bool               TMR_WAKE_UP_FLAG;
extern              _Bool               PBTN_WAKE_UP_FLAG;
extern              _Bool               SYS_PWR_ON_FLAG;                    // SYStem-PoWeR-ON-FLAG.    
extern  volatile    _Bool               SAL_SIG_DET;                        // SALutron SIGnal-DETection.               (NOTE: 1=When a Signal is Present, Default=0)
extern              _Bool               PWR_DSP_FLAG;                       // PoWeR-DiSPlay-screen-FLAG.
extern              _Bool               SAL_DSP_FLAG;                       // SALutron-DiSPlay readout screen FLAG.
extern              _Bool               CHR;                                // State of the SALutron-MODE line.
extern              _Bool               WHR;                                // State of the SALutron-MODE line.
extern  volatile    _Bool               DSP_SET_FLAG;   
extern  volatile    _Bool               PBTN_DET_FLAG;
extern              _Bool               SKIP_INIT; 

extern  volatile    uint16_t            DSP_MODE_TMR;                       // DiSPlay-MODE-TiMeR, 1mS intervals.
extern  volatile    uint16_t            PBTN_DB_TMR;                        // Push-BuTtoN-De-Bouce-TiMeR, 1mS intervals.
extern              uint8_t             BAT_LEVEL;
extern              uint16_t            BAT_BAR_COLOR;
extern              uint32_t            PRVS_BAT_LVL;
extern              uint32_t            CRNT_BAT_LVL;

extern              RTC_TimeTypeDef     RTC_Time;
extern              RTC_DateTypeDef     RTC_Date;
extern              I2C_AXP192          PMIC;    
extern              M5Display           LCD;
extern              MPU6886             IMU;               

//──────────────────────────── DEVICE FUNCTIONS ───────────────────────────────

extern    void    BackLightControl(void);                                   // Control the Display's Backlight and mode.
extern    void    DisplayUpdate(void);                                      // Updates Display with new values based on timers.
extern    void    DisplaySplash(void);                                      // Display the True Fitness Splash screen.
//extern    void    DisplayInit(void);                                        // Display Initalization for the default screen.
extern    void    DisplaySalutron(void);                                    // Display's the Salutron's data screen.
extern    void    DisplayPowerMonitor(void);                                // Display's the Power-Monitor's datascreen.
extern    void    DataLoggerUpdate(void);                                   // Write data to the SD-LOGger.
extern    void    VCP_DataUpdate(void);                                     // Writes data to VCP to confirm whats on SD card.
extern    _Bool   ButtonCheck(void);                                        // Checks the status of the push Buttons.
extern    float   Calculate_HR(void);                                       // Calculate the current Heat-Rate in BPM.
extern    _Bool   MotionCheck(void);
extern    void    LPM_WakeUp(void);                                         // Lower-Power-Mode-Wake-Up routine.
extern    void    LPM_ShutDown(void);                                       // Lower-Power-Mode-Shut-Down routine.
/*
extern    float   Calculate_HR(void);
extern    void    DataLoggerUpdate(void);                                   // Write data to the SD-LOGger.          
extern    void    DisplayUpdate(void);
extern    void    DisplaySplash(void);
extern    void    DisplayInit(void);
extern    void    DisplaySalutron(void);                                    // Displays the Salutron Data.
extern    void    LPM_WakeUp(void);
extern    void    LPM_ShutDown(void);
*/
#endif