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
    File:       Constants.h           -Contains system constants used through the entire program.
    Software:   0121400               -Software number.
    Board:      M5Stick-C Plus        -Color Display, WiFi, Bluetooth, Three switchs, Red & Ir LEDs, IMU, PMU, RTC, Various I/O.
                                       will include an external 18650 Hat, and a proto Hat with the µSD data logger.  Interface
                                       to the Salutron will be through the "GROVE" header.

    Software Supplement: 0121800 REV-1.0.0.XLS.     (Yet to Be Created)
    
───────────────────────── REVISION RECORD ───────────────────────────
    
    ***** SEE 0121400-REV-X.X.X main.cpp FOR REVISION DETAILS *****

─────────────────────────────────────────────────────────────────────
*/

#ifndef     _Constants_h_
#define     _Constants_h_

//#include    <esp_wifi.h>
//#include    <esp_bt.h>
#include    <Arduino.h>
#include    <M5StickCPlus.h>
#include    <M5Display.h>
#include    <I2C_AXP192.h>
#include    <Wire.h>
#include    <RTC.h>
#include    "utility/MPU6886.h"
#include    "utility/Speaker.h"
#include    "driver/adc.h"
#include    "stdio.h"
#include    "time.h"
#include    "Generic.h"
#include    "TF_SPLASH_1.h"
#include    "PMU_Screen_1.h"
#include    "SAL_Screen_1.h"
#include    "driver/gpio.h"
#include    "driver/rtc_io.h"

//──────────────────── UNIT-TEST DEFINITIONS ────────────────────────

#define     VCP_SD_LOG_T        (_ENABLED)                  // Change the valve to (_ENABLED or _DISABLED) for control console communications-Testing of the SD card.
#define     VCP_STATE_T         (_ENABLED)                  // Change the valve to (_ENABLED or _DISABLED) for control console communications-Testing.
#define     LCD_DSP_T           (_ENABLED)                  // Change the valve to (_ENABLED or _DISABLED) for control LCD-Display-Test functions.
#define     DSP_LOGO_T          (_ENABLED)                  // Change the valve to (_ENABLED or _DISABLED) for control to Display the True Fitnesss Logo.   (Graphical)
#define     LCD_TXT_DSP_T       (_DISABLED)                 // Change the valve to (_ENABLED or _DISABLED) for control to Display the True Fitnesss Logo.   (Plain Text)
#define     DSP_MAIN_SCR        (_ENABLED)                  // Change the valve to (_ENABLED or _DISABLED) for control to Display the Main SCReen.
#define     DSP_UPDATE_T        (_ENABLED)                  // Change the valve to (_ENABLED or _DISABLED) for control to UPDATE the Display.
#define     DEBUG_IO_T          (_DISABLED)                 // Change the valve to (_ENABLED or _DISABLED) for control DEBUG-Test-point-Inputs/Outputs.
#define     SD_LOGGER_T         (_ENABLED)                  // Change the valve to (_ENABLED or _DISABLED) for control of the SD Data-LOGGER-Testing.
#define     RTC_T               (_ENABLED)                  // Change the valve to (_ENABLED or _DISABLED) for control of the RTC-Testing.
#define     SET_RTC_T           (_DISABLED)                 // Change the valve to (_ENABLED or _DISABLED) for control of Setting-RTC-Testing.
#define     IMU_T               (_DISABLED)                 // Change the valve to (_ENABLED or _DISABLED) for control of IMU-Testing.
#define     DEEPSLEEP_T         (_ENABLED)                  // Change the valve to (_ENABLED or _DISABLED) for control of DEEP-SLEEP-Testing.
#define     PMIC_STATE_T        (_ENABLED)                  // Change the valve to (_ENABLED or _DISABLED) for control of PMIC-Testing.

//──────────────────────────── UNIT-MODULE NAMES ──────────────────────────────

#define     RTC                 M5.Rtc                      // Define M5's Rtc as RTC.
#define     AXP                 M5.Axp                      // Define M5's Axp as AXP.
#define     I2C                 Wire1                       // Define Wire-1 as I²C bus.
#define     VCP                 Serial                      // Define Serial port as Virtual-Communications-Port(VCP).
#define     SD_LGR              Serial2                     // Define Serial-2 port as SD-data-LoGgeR.

//────────────────────────── PORT PIN DEFINITIONS ─────────────────────────────

#define     GPIO_0              (0u)                        // GPIO-0       (USED)
#define     GPIO_1              (1u)                        // GPIO-1            
#define     GPIO_3              (3u)                        // GPIO-3            
#define     GPIO_5              (5u)                        // GPIO-5       (USED)
#define     GPIO_9              (9u)                        // GPIO-9       (USED)     
#define     GPIO_10             (10u)                       // GPIO-10      (USED)
#define     GPIO_13             (13u)                       // GPIO-13            
#define     GPIO_15             (15u)                       // GPIO-15      (USED)
#define     GPIO_18             (18u)                       // GPIO-18      (USED)
#define     GPIO_21             (21u)                       // GPIO-21      (USED)
#define     GPIO_22             (22u)                       // GPIO-22      (USED)
#define     GPIO_23             (23u)                       // GPIO-23            
#define     GPIO_25             (25u)                       // GPIO-25      (USED)
#define     GPIO_26             (26u)                       // GPIO-26      (USED)
#define     GPIO_27             (27u)                       // GPIO-27
#define     GPIO_32             (32u)                       // GPIO-32      (USED)
#define     GPIO_33             (33u)                       // GPIO-33      (USED)      
#define     GPIO_34             (34u)                       // GPIO-34            
#define     GPIO_35             (35u)                       // GPIO-35      (USED)      
#define     GPIO_36             (36u)                       // GPIO-36                  (INPUT ONLY)
#define     GPIO_37             (37u)                       // GPIO-37      (USED)      
#define     GPIO_39             (39u)                       // GPIO-39      (USED)

//──────────────────────── USED PORT PIN DEFINITIONS ──────────────────────────

#define     TXO_TO_LGR          (GPIO_0)                    // TX-Out to SD-LoGgeR.                 (Hat Expansion Port)
#define     IR_LED              (GPIO_9)                    // Internal InfraRed-LED.
#define     RED_LED             (GPIO_10)                   // Internal RED-LED.
#define     SDA                 (GPIO_21)                   // SDA, I²C Serial DAta Line I/O.
#define     SCL                 (GPIO_22)                   // SCL, I²C Serial CLock OUTPUT.
#define     TST_PIN             (GPIO_25)                   // TeST-PIN-I/O.                        (Hat Expansion Port)
#define     RXI_FROM_LGR        (GPIO_26)                   // RX-Input from SD-LoGgeR.             (Hat Expansion Port)
#define     SAL_PULSE           (GPIO_32)                   // SALutron-PULSE-Input.                (GROVE PORT)     (0x100000000)
#define     SAL_MODE            (GPIO_33)                   // SALutron-MODE-Input.                 (GROVE PORT)     (0x200000000)
#define     RTC_EN              (GPIO_34)                   // RTC-ENable-Output.                   (Was MIC SDA)
#define     PBTN_F              (GPIO_37)                   // Front-Push-BuTtoN.                   (BUTTON_A)      (0x2000000000)
#define     PBTN_T              (GPIO_39)                   // Top--Push-BuTtoN.                    (BUTTON_B)      (0x8000000000)
#define     SYS_INT             (GPIO_35)                   // SYStemwide shared INTerrput input.                    (0x800000000)

//────────────────────────── ISR-TIMER DEFINITIONS ────────────────────────────

#define     PBTN_DB_TME         (50u)                       // Push-BuTtoN-De-Bouce-TiME in mS.
#define     LED_ON_TME          (15u)                       // LED-ON-TiME in mS.
#define     LCD_ON_TME          (10000u)                    // LCD-DiSPlay-TiME in mS.
#define     SD_LGR_TME          (100u)                      // µSD Card-LoGgeR-TiME in mS.
#define     SYS_ACT_TME         (25000u)                    // SYStem-ACTivity-TiME in mS.
#define     DSP_MODE_TME        (250u)                      // SYStem-ACTivity-TiME in mS.

//───────────────────────── VCP-Command DEFINITIONS ───────────────────────────

#define     HOME_CURSOR         ("\e[1;1H")                 // HOME the CURSOR in the terminal.
#define     CLEAR_SCREEN        ("\e[2J\e[1;1H")            // CLEAR the SCREEN in the terminal.    

//───────────────────────────── LCD DEFINITIONS ───────────────────────────────

#define     LCD_BL_OFF          (OFF)                       // Turn the LCD-Back-Light-OFF.
#define     LCD_BL_DIM          (2700u)                     // 2.700V for a DIM-LCD-Back-Light.
#define     LCD_BL_BRT          (2950u)                     // 2.950V for a BRighT-LCD-Back-Light.

//──────────────────────────── PMIC DEFINITIONS ───────────────────────────────

#define     EXT_5V_ON           (ON)                        // Turn ON the EXTernal 5V step-up supply.
#define     EXT_5V_OFF          (OFF)                       // Turn OFF the EXTernal 5V step-up supply.
#define     RTC_BCKUP_ON        (ON)                        // Turn ON the RTC-BaCK-UP battery.
#define     RTC_BCKUP_OFF       (OFF)                       // Turn OFF the RTC-BaCK-UP battery.
#define     MIC_PWR_ON          (2800u)                     // 2.800V to PoWeR the MIC-ON.
#define     MIC_PWR_OFF         (OFF)                       // Turn the MIC-PoWeR-OFF.
#define     PMIC_ADR            (0x34)                      // PMIC (AXP192) Sub-ADdRess.
#define     GPIO0_CTRL_REG      (0x90)                      // PMIC's GPIO0-ConTRoL-REGister address.
#define     GPIO1_CTRL_REG      (0x92)                      // PMIC's GPIO1-ConTRoL-REGister address.
#define     GPIO2_CTRL_REG      (0x93)                      // PMIC's GPIO2-ConTRoL-REGister address.
#define     ADC_EN1_CTRL_REG    (0x82)                      // PMIC's ADC-ENable-1-ConTRoL-REGister address.
#define     ADC_EN2_CTRL_REG    (0x83)                      // PMIC's ADC-ENable-2-ConTRoL-REGister address.
#define     ADC_SR_TS_CTRL_REG  (0x84)                      // PMIC's ADC-Temperature-Sensor-ConTRoL-REGister address.
#define     OVR_TMP_CTRL_REG    (0x8F)                      // PMIC's OVeR-TeMPerature-ConTRoL-REGister address.
#define     BAT_BKUP_CTRL_REG   (0x35)                      // PMIC's BATtery-BacK-UP-ConTRoL-REGister address.
#define     DCDC_1_3_CTRL_REG   (0x12)                      // PMIC's DC-DC-1&3-ConTRoL-REGister address.
#define     LDO_2_3_CTRL_REG    (0x12)                      // PMIC's LDO-2&3-ConTRoL-REGister address.
#define     DCDC_2_CTRL_REG     (0x10)                      // PMIC's DC-DC-1&3-ConTRoL-REGister address.

//──────────────── PMIC BIT DEFINITIONS ───────────────────

#define     GPIOx_FLOAT         (0b00000110)                // PMIC's GPIO-x's value for FLOATing pin state.
#define     BAT_BKUP_CHRG_EN    (0b00100000)                // PMIC's BATtery-BacK-UP-CHaRGe-ENable control.
#define     DCDC_1_PWR_EN       (0b00000001)                // PMIC's DC-DC-1-PoWeR-ENable control.
#define     TS_PIN_CRNT         (0b00000011)                // PMIC's Temperature-Sensor-PIN-CuRreNT settings.
#define     OVR_TMP_EN          (0b00000100)                // PMIC's OVeR-TeMPerature-ENable, reverse logic.

//───────────────────────────── RTC DEFINITIONS ───────────────────────────────

#define     RTC_ADR             (0x51)
#define     CLKOUT_REG          (0x0D)
#define     VL_SEC_REG          (0x02)
#define     VL_FLAG             (7u)


// __DATE__ string: "Jul   27   201 2"
//        Position:  012 3 45 6 789 10
// __TIME__ string: "21:06:19"
//        Position:  01234567

#define COMPUTE_BUILD_YEAR \
    ( \
        (__DATE__[ 7] - '0') * 1000 + \
        (__DATE__[ 8] - '0') *  100 + \
        (__DATE__[ 9] - '0') *   10 + \
        (__DATE__[10] - '0') \
    )

#define COMPUTE_BUILD_DAY \
    ( \
        ((__DATE__[4] >= '0') ? (__DATE__[4] - '0') * 10 : 0) + \
        (__DATE__[5] - '0') \
    )

#define BUILD_MONTH_IS_JAN (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')
#define BUILD_MONTH_IS_FEB (__DATE__[0] == 'F')
#define BUILD_MONTH_IS_MAR (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
#define BUILD_MONTH_IS_APR (__DATE__[0] == 'A' && __DATE__[1] == 'p')
#define BUILD_MONTH_IS_MAY (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
#define BUILD_MONTH_IS_JUN (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
#define BUILD_MONTH_IS_JUL (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l')
#define BUILD_MONTH_IS_AUG (__DATE__[0] == 'A' && __DATE__[1] == 'u')
#define BUILD_MONTH_IS_SEP (__DATE__[0] == 'S')
#define BUILD_MONTH_IS_OCT (__DATE__[0] == 'O')
#define BUILD_MONTH_IS_NOV (__DATE__[0] == 'N')
#define BUILD_MONTH_IS_DEC (__DATE__[0] == 'D')
#define COMPUTE_BUILD_MONTH \
    ( \
        (BUILD_MONTH_IS_JAN) ?  1 : \
        (BUILD_MONTH_IS_FEB) ?  2 : \
        (BUILD_MONTH_IS_MAR) ?  3 : \
        (BUILD_MONTH_IS_APR) ?  4 : \
        (BUILD_MONTH_IS_MAY) ?  5 : \
        (BUILD_MONTH_IS_JUN) ?  6 : \
        (BUILD_MONTH_IS_JUL) ?  7 : \
        (BUILD_MONTH_IS_AUG) ?  8 : \
        (BUILD_MONTH_IS_SEP) ?  9 : \
        (BUILD_MONTH_IS_OCT) ? 10 : \
        (BUILD_MONTH_IS_NOV) ? 11 : \
        (BUILD_MONTH_IS_DEC) ? 12 : \
        /* error default */  99 \
    )

#define COMPUTE_BUILD_HOUR ((__TIME__[0] - '0') * 10 + __TIME__[1] - '0')
#define COMPUTE_BUILD_MIN  ((__TIME__[3] - '0') * 10 + __TIME__[4] - '0')
#define COMPUTE_BUILD_SEC  ((__TIME__[6] - '0') * 10 + __TIME__[7] - '0')

#define BUILD_DATE_IS_BAD (__DATE__[0] == '?')
#define BUILD_YEAR  ((BUILD_DATE_IS_BAD) ? 99 : COMPUTE_BUILD_YEAR)
#define BUILD_MONTH ((BUILD_DATE_IS_BAD) ? 99 : COMPUTE_BUILD_MONTH)
#define BUILD_DAY   ((BUILD_DATE_IS_BAD) ? 99 : COMPUTE_BUILD_DAY)

#define BUILD_TIME_IS_BAD (__TIME__[0] == '?')
#define BUILD_HOUR  ((BUILD_TIME_IS_BAD) ? 99 :  COMPUTE_BUILD_HOUR)
#define BUILD_MIN   ((BUILD_TIME_IS_BAD) ? 99 :  COMPUTE_BUILD_MIN)
#define BUILD_SEC   ((BUILD_TIME_IS_BAD) ? 99 :  COMPUTE_BUILD_SEC)

//───────────────────────────── IMU DEFINITIONS ───────────────────────────────

#define     IMU_PWR             (2800u)                     // IMU-PoWeR setting.
#define     IMU_ADR             (0x68)                      // IMU-Sub-ADdRess.
#define     IMU_ACCEL_CFG_1     (0x1C)                      // IMU-ACCELeration-ConFiGuration-1-Register.
#define     IMU_ACCEL_CFG_2     (0x1D)                      // IMU-ACCELeration-ConFiGuration-2-Register.
#define     IMU_ACCL_WOM_X_THR  (0x20)                      // IMU-ACCELeration-WOM-X axis-THReshold-Register.
#define     IMU_ACCL_WOM_Y_THR  (0x21)                      // IMU-ACCELeration-WOM-Y axis-THReshold-Register.
#define     IMU_ACCL_WOM_Z_THR  (0x22)                      // IMU-ACCELeration-WOM-Z axis-THReshold-Register.
#define     IMU_INT_PIN_CFG     (0x37)                      // IMU-INTerrupt-PIN-ConFiGuration-Register.
#define     IMU_INT_EN          (0x38)                      // IMU-INTerrupt-ENable-Register.
#define     IMU_INT_STAT        (0x3A)                      // IMU-INTerrupt-STATus-Register.
#define     ACCEL_INTEL_CTRL    (0x69)                      // ACCELerometer-INTELligence-ConTRL-Register.
#define     IMU_PWR_MGMT_1      (0x6B)                      // IMU-PoWeR-ManaGeMenT-1-Register.
#define     IMU_PWR_MGMT_2      (0x6C)                      // IMU-PoWeR-ManaGeMenT-2-Register.
#define     IMU_INT_EN_REG      (0x38)                      // IMU-INTerrupt-ENable-REGister.

//──────────────── IMU BIT DEFINITIONS ────────────────────

#define     IMU_SLP_FLAG        (0b01000000)                // IMU-SLeeP-FLAG.
#define     ACCEL_FS_SEL        (0b00011000)                // ACCELerometer-Full-Scale-SELect bits.
#define     A_DLPF_CFG          (0b00000001)                // Bit Position of A-DLPF-CFG in ACCEL-CFG-2.
#define     ACCEL_FCHOICE_B     (0b00001000)                // Bit Position of ACCEL-FCHOICE-B in ACCEL-CFG-2.
#define     DEC2_CFG            (0b00100000)                // 16 sample average pattern, Bits[5,4].
#define     WOM_X_INT_EN        (0b10000000)                // WOM-X axis-INT-ENable bit.
#define     WOM_Y_INT_EN        (0b01000000)                // WOM-Y axis-INT-ENable bit.
#define     WOM_Z_INT_EN        (0b00100000)                // WOM-Z axis-INT-ENable bit.
#define     WOM_THR_VALUE       (0b00011111)                // WOM-THReshold-VALUE for all 3-axies.

//───────────────────────── LCD-DiSPlay DEFINITIONS ───────────────────────────

#define     SCREEN_WIDTH_p      (135u)                      // LCD DiSPlay width, in pixels.                (Portrait)
#define     SCREEN_HEIGHT_p     (240u)                      // LCD DiSPlay height, in pixels.               (Portrait)
#define     SCREEN_WIDTH_l      (240u)                      // LCD DiSPlay width, in pixels.                (Landscape)
#define     SCREEN_HEIGHT_l     (135u)                      // LCD DiSPlay height, in pixels.               (Landscape)
#define     BAT_LEVEL_MIN       (118u)                      // LCD Battery-Level-Minimum pixel location.
#define     BAT_LEVEL_MAX       (18u)                       // LCD Battery-Level-Maximum pixel location.

//────────────────────────── SALUTRON DEFINITIONS ─────────────────────────────

#define     MAX_SAL_SIG_TME     (125u)                      // SALutron-SIGnal-TiME to determine if Salutron is active in mS.

//───────────────────────── DEEP-SLEEP DEFINITIONS ────────────────────────────

#define     SAL_PULSE_WAKEUP    (GPIO_NUM_32)               // Position of the GPIO pin.
#define     SAL_MODE_WAKEUP     (GPIO_NUM_33)               // Position of the GPIO pin.
#define     PBTN_F_WAKEUP       (2^GPIO_NUM_37)             // Position of the GPIO pin.
#define     PBTN_T_WAKEUP       (2^PBTN_T)                  // Position of the GPIO pin.
#define     SYS_INT_WAKEUP      (2^SYS_INT)                 // Position of the GPIO pin.
#define     uS2S_Facter         (1000000u)                  // Conversion factor for micro seconds to seconds.
#define     Sec_Sleep           (3600u)                     // Time ESP32 will go to sleep (in seconds).
#define     SleepTime           (uS2S_Facter*Sec_Sleep)     // Sleep-Time in µS.

//──────────────────────── UNIT MODE BIT DEFINITIONS ──────────────────────────
/*
#define     INIT_MODE_FLAG      (0u)                        // INITialization to be RUN.            (1=RUN Initalization Code, 0=Unit waking from deep sleep.)
#define     UNIT_SLP_FLAG       (1u)                        // UNIT-SLeeP-FLAG.                     
#define     UNIT_RUN_FLAG       (2u)                        // UNIT-RUN-FLAG.        
#define     GPIO_WAKE_UP_FLAG   (3u)                        // GPIO-WAKE-UP-FLAG.
#define     TMR_WAKE_UP_FLAG    (4u)                        // TiMeR-WAKE-UP-FLAG.

#define     LCD_BL_EN_FLAG      (5u)                        // LCD-Back-Light-ENable-FLAG.
#define     LCD_PWR_EN_FLAG     (6u)                        // LCD-PoWeR-ENable-FLAG.
#define     LED_EN_FLAG         (7u)                        // LED-ENable-FLAG.
#define     IMU_PWR_FLAG        (8u)                        // IMU-PoWeR-FLAG.
#define     SD_LOG_FLAG         (9u)                        // µSD Card-LOGger-FLAG.                (1=Passed tests and ready for data, 0=Failed tests.)

#define     SCR_TGL_FLAG        (10u)                        // ToGgLe-SCReen-FLAG.
#define     PWR_DSP_FLAG        (11u)                       // PoWeR-DiSPlay-screen-FLAG.
#define     SAL_DSP_FLAG        (12u)                       // SALutron-DiSPlay-screen-FLAG.
#define     SCR_DSP_FLAG        (13u)                       // SCReeN-DiSPlay-FLAG.

#define     SAL_SIG_FLAG        (14u)                       // SALutron-sPulse-SIGnal-active-FLAG.
#define     SAL_CHR_FLAG        (15u)                       // SALutron-Contact-Heart-Rate-FLAG.
#define     SAL_WHR_FLAG        (16u)                       // SALutron-Wireless-Heart-Rate-FLAG.

#define     PBTN_DET_FLAG       (17u)                       // SET when a button press is detected.


*/
//────────────────────────── UNIT TIMER DEFINITIONS ───────────────────────────
/*
#define     LED_ON_TMR          (0u)                        // Position of the TiMeR in the UNIT_TMRS array.
#define     LCD_ON_TMR          (1u)                        // Position of the TiMeR in the UNIT_TMRS array.
#define     PBTN_DB_TMR         (2u)                        // Position of the TiMeR in the UNIT_TMRS array.
#define     SD_LOG_TMR          (3u)                        // Position of the TiMeR in the UNIT_TMRS array.
#define     DSP_MODE_TMR        (4u)                        // Position of the TiMeR in the UNIT_TMRS array.
#define     SYS_ACT_TMR         (5u)                        // Position of the TiMeR in the UNIT_TMRS array.
#define     sPULSE_HIGH_TMR     (6u)                        // Position of the TiMeR in the UNIT_TMRS array.
#define     sPULSE_LOW_TMR      (7u)                        // Position of the TiMeR in the UNIT_TMRS array.
*/
//───────────────────────────── Salutron-MACROS ───────────────────────────────

#define     NoSalutronInput     ((digitalRead(SAL_PULSE))&&(digitalRead(SAL_MODE)))
#define     SalutronContact     ((!digitalRead(SAL_PULSE))&&(!digitalRead(SAL_MODE)))
#define     SalutronWireless    ((!digitalRead(SAL_PULSE))&&(digitalRead(SAL_MODE)))

//──────────────────────────── Push-Button-MACROS ─────────────────────────────

#define     FRONT_PB            ((!digitalRead(PBTN_F)) && (digitalRead(PBTN_T)))
#define     TOP_PB              ((digitalRead(PBTN_F)) && (!digitalRead(PBTN_T)))

#endif
/* END OF FILE. */