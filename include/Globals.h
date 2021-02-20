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
    File:       Globals.h             -Contains system variables and function prototypes used in the entire program.
    Software:   0121400               -Software number.
    Board:      M5Stick-C Plus        -Color Display, WiFi, Bluetooth, Three switchs, Red & Ir LEDs, IMU, PMU, RTC, Various I/O.
                                       will include an external 18650 Hat, and a proto Hat with the µSD data logger.  Interface
                                       to the Salutron will be through the "GROVE" header.

    Software Supplement: 0121800 REV-1.0.0.XLS.     (Yet to Be Created)
    
───────────────────────── REVISION RECORD ───────────────────────────
    
    ***** SEE 0121400-REV-X.X.X main.cpp FOR REVISION DETAILS *****

─────────────────────────────────────────────────────────────────────
*/

//────────────────────────────── UNIT-INCLUDES ────────────────────────────────

#include    "Constants.h"                                       // Include Gloabal constants.
//#include    <WiFi.h>
//#include    <esp32-hal-bt.c>

//──────────────────────── RTC-DEEP-SLEEP VARIABLES ───────────────────────────

    RTC_DATA_ATTR   uint32_t        DS_CRNT_PULSE_CNT;
    RTC_DATA_ATTR   uint32_t        DS_PRVS_PULSE_CNT;
    RTC_DATA_ATTR   int16_t         DS_ACC_X_CAL_VAL;
    RTC_DATA_ATTR   int16_t         DS_ACC_Y_CAL_VAL;
    RTC_DATA_ATTR   int16_t         DS_ACC_Z_CAL_VAL;

//─────────────────────────────────────────────────────────────────────────────  

//──────────────────── UNIT-PERIPHIAL CLASS DEFINITIONS ───────────────────────

        extern const unsigned char TF_logo[64800];              // Spalsh Screen.           (FLASH)
        extern const unsigned char SAL_SCR[64800];              // SALutron-SCReen.         (FLASH, Default screen.)
        extern const unsigned char PMU_SCR[64800];              // PMU-DisplaySCReen.       (FLASH)

        RTC_TimeTypeDef         RTC_Time;
        RTC_DateTypeDef         RTC_Date;
        M5Display               LCD;
        I2C_AXP192              PMIC(PMIC_ADR,I2C);        
        TFT_eSprite             DSP_BFR=TFT_eSprite(&LCD);          // Setup the DSP_BFR for the LCD Display.
        SPEAKER                 Speaker;             
        MPU6886                 IMU;                     
//─────────────────────────────────────────────────────────────────────────────  

//─────────────────────────── UNIT-MODE VARIABLES ─────────────────────────────

        volatile    uint32_t    UNIT_MODE;                      // Contains all UNIT control bits for various conditions.
        volatile    uint16_t    UNIT_TMRS[10];                  // Contains all UNIT TiMeRS for all timing requirements.
                    uint8_t     I2C_BFR[16];

//─────────────────────────── ISR TIMER VARIABLES ─────────────────────────────

        portMUX_TYPE GPIO_SYNC=portMUX_INITIALIZER_UNLOCKED;    // Port-I/O interrupt synchronozation initialzer.
        portMUX_TYPE HW_TMR=portMUX_INITIALIZER_UNLOCKED;       // HW-TiMeR interrupt synchronozation initialzer.
        hw_timer_t * HW_TMR_0=NULL;                             // Setup the HW-TiMeR-0.

        volatile    _Bool       LCD_BL_EN_FLAG;                 // LCD-Back-Light-ENable-FLAG.
        volatile    _Bool       LED_EN_FLAG;                    // LED-ENable-FLAG.
        volatile    _Bool       PWR_DSP_FLAG;                   // PoWeR-DiSPlay-screen-FLAG.
        volatile    _Bool       SAL_DSP_FLAG;                   // SALutron-DiSPlay readout screen FLAG.
                    _Bool       SYS_PWR_ON_FLAG=SET;            // SYStem-PoWeR-ON-FLAG.
                    _Bool       GPIO_WAKE_UP_FLAG;
                    _Bool       TMR_WAKE_UP_FLAG;
                    _Bool       PBTN_WAKE_UP_FLAG;
                    _Bool       RUN_INIT;
                    _Bool       SKIP_INIT;
        volatile    _Bool       DSP_SET_FLAG;
        volatile    _Bool       DSP_UPDATE_FLAG;        
        volatile    _Bool       PBTN_DET_FLAG;

        volatile    uint8_t     LED_ON_TMR;                     // LED-ON-TiMeR 1mS intervals.
        volatile    uint16_t    LCD_ON_TMR;                     // LCD-DiSPlay-TiMeR, 1mS intervals.
        volatile    uint16_t    PBTN_DB_TMR;                    // Push-BuTtoN-De-Bouce-TiMeR, 1mS intervals.
        volatile    uint16_t    DSP_MODE_TMR;                   // DiSPlay-MODE-TiMeR, 1mS intervals.
        volatile    uint16_t    SYS_ACT_TMR;                    // SYStem-ACTivity-TiMeR, before sleep, 1mS intervals.
        
//─────────────────────────────────────────────────────────────────────────────  

//──────────────────────────── SALUTRON VARIABLES ─────────────────────────────

/*
                    _Bool       SAL_CHR_FLAG;                   // SALutron-Contact-HR-FLAG.
                    _Bool       SAL_WHR_FLAG;                   // SALutron-Wireless-HR-FLAG.
                    float       PULSE_RATE;                     // Calculated PULSE-RATE.
*/                    

        volatile    uint32_t    sPULSE_START_TME;               // SALutron-sPulse START-TiME.
        volatile    uint32_t    sPULSE_STOP_TME;                // SALutron-sPulse STOP-TiME.
        volatile    uint32_t    sPULSE_ELAPSED_TME;             // SALutron-sPulse ELAPSED-TiME.
        volatile    uint32_t    sPULSE_HIGH_TME;                // SALutron-sPulse START-TiME.
        volatile    _Bool       SAL_SIG_DET;                    // SALutron-SIGnal-DETection.           (NOTE: 1=When a Signal is Present, Default=0)
                    _Bool       CHR;                            // State of the SALutron-MODE line.
                    _Bool       WHR;                            // State of the SALutron-MODE line.
                    float       HR_Value;                       // Calculated Heart-Rate.

        volatile    uint32_t    PRVS_PULSE_CNT;                  // PReViouS-PULSE-CouNT.
        volatile    uint32_t    CRNT_PULSE_CNT;                  // CuRreNT-Accumulated PULSE-CouNT.

//─────────────────────────────────────────────────────────────────────────────  

//─────────────────────────── SD-LOGGER VARIABLES ─────────────────────────────

                    _Bool       SD_LGR_FLAG;                    // SD-LoGgeR-FLAG bit.
        volatile    uint8_t     SD_LOG_TMR;                     // 8-Bit 1mS OPEN-LOG-TiMeR.

//─────────────────────────────────────────────────────────────────────────────  

//────────────────────────────── RTC VARIABLES ────────────────────────────────

                    uint8_t     PRVS_SECOND;                    // PReViouS SECOND.                    
                    uint8_t     PRVS_DAY;                       // PReViouS DAY.                    

//─────────────────────────────────────────────────────────────────────────────  

///────────────────────────────── IMU VARIABLES ────────────────────────────────
                    
                    uint8_t     INT_STATUS;
        volatile    uint16_t    IMU_CHK_TMR;
                    _Bool       IMU_INIT_FLAG;
                    _Bool       IMU_DET_FLAG;
                    uint8_t     IMU_WOM_THLD=WOM_THR_VALUE;
                    uint8_t     IMU_DET_THLD=40;

                    float       accX=0.0f;
                    float       accY=0.0f;
                    float       accZ=0.0f;

                    float       CRNT_ACC_X=CLEAR;
                    float       CRNT_ACC_Y=CLEAR;
                    float       CRNT_ACC_Z=CLEAR;

                    int16_t     AVG_ACC_X=CLEAR;
                    int16_t     AVG_ACC_Y=CLEAR;
                    int16_t     AVG_ACC_Z=CLEAR;

//─────────────────────────────────────────────────────────────────────────────  

//─────────────────────────── GRAPHICS VARIABLES ──────────────────────────────

                    uint8_t     BAT_LEVEL;
                    uint8_t     BAT_PXL_LEVEL;
                    uint16_t    BAT_BAR_COLOR;
                    uint32_t    PRVS_BAT_LVL;
                    uint32_t    CRNT_BAT_LVL;

//─────────────────────────────────────────────────────────────────────────────  

//───────────────────────── ISR FUNCTION PROTOTYPES ───────────────────────────

void    IRAM_ATTR   SAL_CHK_ISR(void);                          // CHecK-SALutron-Interrupt-Service-Routine.  
void    IRAM_ATTR   SYS_CHK_ISR(void);                          // CHecK SYStem-Interrupt-Service Routine.
void    IRAM_ATTR   BTN_CHK_ISR(void);                          // CHecK BuTtoN-Interrupt-Service-Routine.
void    IRAM_ATTR   TMR_CHK_ISR(void);                          // CHecK TiMeR-Interrupt-Service-Routine.

//─────────────────────────────────────────────────────────────────────────────  

//────────────────────────── FUNCTION PROTOTYPES ──────────────────────────────

void    BackLightControl(void);                                 // Control the Display's Backlight and mode.
void    DisplayUpdate(void);                                    // Updates Display with new values based on timers.
void    DisplaySplash(void);                                    // Display the True Fitness Splash screen.
void    DisplayInit(void);                                      // Display Initalization for the default screen.
void    DisplaySalutron(void);                                  // Display's the Salutron's data screen.
void    DisplayPowerMonitor(void);                              // Display's the Power-Monitor's datascreen.
void    DataLoggerUpdate(void);                                 // Write data to the SD-LOGger.
void    VCP_DataUpdate(void);                                   // Writes data to VCP to confirm whats on SD card.
_Bool   ButtonCheck(void);                                      // Checks the status of the push Buttons.
float   Calculate_HR(void);                                     // Calculate the current Heat-Rate in BPM.
_Bool   MotionCheck(void);                                      // Checks the IMU for motion on the equipment.
void    IMU_Calibration(void);                                  // IMU-Calibration.  This should only occur upon inital power ON.
void    PMIC_CLR_IRQ(void);                                     // CLeaRs the PMIC IRQ's at startup.
void    PMIC_TMP_MNTR(_Bool);                                   // Enable/Disable the PMIC TeMPerature-MoNiToR.
void    PMIC_OVT_MNTR(_Bool);                                   // Enable/Disable the PMIC OVer-Temperature-MoNiToR module.
void    PMIC_RTC_BKUP_CHRG(_Bool,uint8_t);                      // Enable/Disable the PMIC-RTC-battery-BacK-UP CHaRGer and the charging current.
void    LPM_WakeUp(void);                                       // Lower-Power-Mode-Wake-Up routine.
void    LPM_ShutDown(void);                                     // Lower-Power-Mode-Shut-Down routine.
void    setup(void)                                             // setup Function Declaration.
{
//──────────────────────── M5STICK-C INITIALIZATION ───────────────────────────

    M5.begin(CLEAR,CLEAR,CLEAR);    
    delay(500);
//    esp_wifi_init(NULL);
//    esp_wifi_deinit();
//    esp_bt_controller_deinit();
    
//─────────────────────────────────────────────────────────────────────────────  

//──────────────────────── PORT PIN INITIALIZATION ────────────────────────────

    pinMode(TXO_TO_LGR,OUTPUT);
    pinMode(TST_PIN,OUTPUT);
    pinMode(RXI_FROM_LGR,INPUT);
    pinMode(RED_LED,INPUT);
    pinMode(IR_LED,INPUT);
    pinMode(PBTN_F,INPUT);
    pinMode(PBTN_T,INPUT);
    pinMode(SYS_INT,INPUT);
    pinMode(SAL_PULSE,INPUT);
    pinMode(SAL_MODE,INPUT);
    
    pinMode(GPIO_5,INPUT);                                      // NOT USED.  
    pinMode(GPIO_13,INPUT);                                     // NOT USED.  
    pinMode(GPIO_15,INPUT);                                     // NOT USED.   
    pinMode(GPIO_23,INPUT);                                     // NOT USED.   
    pinMode(GPIO_34,OUTPUT);                                    // NOT USED.   
    digitalWrite(GPIO_34,LOW);
        
//─────────────────────────────────────────────────────────────────────────────


//──────────────────── Virtual-Comm-Port INITIALIZATION ───────────────────────

    VCP.begin(115200);
    VCP.flush();
    VCP.println();
    delay(50);

//─────────────────────────────────────────────────────────────────────────────  

//───────────────────────── I²C Bus INITIALIZATION ────────────────────────────

    I2C.begin(SDA,SCL);
    delay(250);

//─────────────────────────────────────────────────────────────────────────────    

//──────────────────── INTERRUPT SET-UP INITIALIZATION ────────────────────────
    if(!SKIP_INIT)
    {
        attachInterrupt(SAL_PULSE,SAL_CHK_ISR,RISING);              // CHeck SALutron-sPULSE Interrupt input.        
        attachInterrupt(SYS_INT,SYS_CHK_ISR,FALLING);               // CHeck SYStem shared Interrupt input.
        attachInterrupt(PBTN_F,BTN_CHK_ISR,FALLING);                // CHeck Push BuTtoN-Front Interrupt input.
        attachInterrupt(PBTN_T,BTN_CHK_ISR,FALLING);                // CHecK Push BuTtoN-Top Interrupt input.

        HW_TMR_0=timerBegin(0, 20, true);
        timerAttachInterrupt(HW_TMR_0,&TMR_CHK_ISR,true);
        timerAlarmWrite(HW_TMR_0,1000,true);
        timerAlarmEnable(HW_TMR_0);
    }

//─────────────────────────────────────────────────────────────────────────────  

//─────────────────────────── UNIT-WAKEUP SERVICE ─────────────────────────────

    LPM_WakeUp();
    VCP.print("VCP Ready.\r\n");
    VCP.print("I2C Ready.\r\n");

//─────────────────────────────────────────────────────────────────────────────  

//─────────────────── Power-Management-IC INITIALIZATION ──────────────────────

#if(PMIC_T)
      I2C_AXP192_InitDef  PMU_INIT=
    {   
        .EXTEN=EXT_5V_OFF,                                      // Turn the EXTeral-5V ENable OFF.
        .BACKUP=RTC_BCKUP_OFF,                                  // Turn the RTC-Battery-BaCK-UP-OFF.
        .DCDC1=2800,                                            // Set ESP32 primary valtage to 3.000Vdc.
        .DCDC2=OFF,                                             // Set DC-DC-2 to 0Vdc. 
        .DCDC3=OFF,                                             // Set DC-DC-3 to 0Vdc. 
        .LDO2=LCD_BL_OFF,                                       // Turn the LCD-Back-Light-OFF.
        .LDO3=LCD_CTRL_ON,                                      // Set the LCD-Module ON.
        .GPIO0=IMU_PWR_ON,                                      // Turn the IMU-PoWeR-OFF.
        .GPIO1=NOT_USED,                                        // GPIO-1, NOT USED.    
        .GPIO2=NOT_USED,                                        // GPIO-2, NOT USED.    
        .GPIO3=NOT_USED,                                        // GPIO-3, NOT USED.    
        .GPIO4=NOT_USED,                                        // GPIO-4, NOT USED.    
    };
    PMIC.begin(PMU_INIT);                                       // Start the PMIC.
    AXP.DisableCoulombcounter();                                // In the M5's Library.
    PMIC_CLR_IRQ();                                             // CLEAR out PMIC IRQ's.
    PMIC_TMP_MNTR(ENABLE);                                      // ENable the PMIC Internal Temperature Monitor.
    PMIC_RTC_BKUP_CHRG(ENABLE,BKUP_CHRG_200uA);                 // ENable the RTC battery BacK-UP CHaRGe @ 200µA.

   if(!SKIP_INIT)
   {
        //Turn off the RTC CLK Output.
        I2C.beginTransmission(RTC_ADR);
        I2C.write(CLKOUT_REG);
        I2C.write(CLEAR);
        I2C.endTransmission();    
   }
    VCP.print("PMU Ready.\r\n");
    VCP.print("IMU Ready.\r\n");
#endif    

//─────────────────────────────────────────────────────────────────────────────  

//──────────────── Inertial-Measurement-Unit INITIALIZATION ───────────────────

if(!SKIP_INIT)
{
    delay(10);
    IMU.Init();
    VCP.print("IMU Initializing");
    IMU_Calibration();
}

//───────────────────── Real-Time-Clock INITIALIZATION ────────────────────────

if(!SKIP_INIT)
{

#if(SET_RTC_T)
        RTC_Time.Hours=BUILD_HOUR;
        RTC_Time.Minutes=BUILD_MIN;
        RTC_Time.Seconds=BUILD_SEC;
        M5.Rtc.SetTime(&RTC_Time);
        RTC_Date.Month=BUILD_MONTH;
        RTC_Date.Date=BUILD_DAY;
        RTC_Date.Year=BUILD_YEAR;
        M5.Rtc.SetData(&RTC_Date);

#endif

    // Get the Current Date and Time.
    RTC.begin();
    RTC.GetTime(&RTC_Time);
    RTC.GetData(&RTC_Date);
    VCP.print("RTC Ready.\r\n\r\n");
    VCP.print(String(RTC_Date.Month)+"-"+
              String(RTC_Date.Date)+"-"+
              String(RTC_Date.Year)+",");
    VCP.print(String(RTC_Time.Hours)+":");
    if (RTC_Time.Minutes<10)
      { VCP.print('0'); }
    VCP.print(String(RTC_Time.Minutes)+":");
    if (RTC_Time.Seconds<10)
      { VCP.print('0'); }
    VCP.print(String(RTC_Time.Seconds)+"\r\n\r\n");
    PRVS_SECOND=-1;    
}

//─────────────────────────────────────────────────────────────────────────────

//─────────────────────── LCD DISPlAY INITIALIZATION ──────────────────────────
    
    // Display the Power-Up Splash screen on Initialization.
    DisplaySplash();

//─────────────────────────────────────────────────────────────────────────────

//──────────────────────── SD-LOGGER INITIALIZATION ───────────────────────────

{   //SD-LOGGER Init.
    PMIC.setEXTEN(EXT_5V_ON);
    delay(25);
    SD_LGR.begin(115200,SERIAL_8N1,RXI_FROM_LGR,TXO_TO_LGR);
    delay(250);
    VCP.print("Logger Initalizing...\r\n");
    SD_LGR_FLAG=CLEAR;
    SD_LOG_TMR=SD_LGR_TME;
    while(SD_LOG_TMR)
    {
        if(SD_LGR.available())
        {
            if(SD_LGR.read()=='<')
            {   
                SD_LGR_FLAG=SET;
                VCP.print("Found SD Card.\r\n");                
                break;
            }
        }      
    }

    if(!SD_LOG_TMR)
    {
        VCP.print("SD Error or No card.\r\n");                
        PMIC.setEXTEN(EXT_5V_OFF);
    }

    if(SD_LGR_FLAG)
    {
        SD_LGR.write(26);
        SD_LGR.write(26);
        SD_LGR.write(26);
        SD_LGR_FLAG=CLEAR;
        SD_LOG_TMR=SD_LGR_TME;
        while(SD_LOG_TMR)
        {
            if(SD_LGR.available())
            {
                if(SD_LGR.read()=='>')
                {   
                    SD_LGR_FLAG=SET;
                    VCP.print("Initializing Files...\r\n");                                    
                    break;
                }                                 
            }    
        }
        if(!SD_LOG_TMR)
        {
            VCP.print("SD Error or No card.\r\n");                
            PMIC.setEXTEN(EXT_5V_OFF);
        }
    }
    
    if(SD_LGR_FLAG)
    {
        SD_LGR.print("append SLOG001.csv\r");
        SD_LGR_FLAG=CLEAR;
        SD_LOG_TMR=SD_LGR_TME;
        while(SD_LOG_TMR)
        {
            if(SD_LGR.available())
            {            
                if(SD_LGR.read()=='<')
                {
                    SD_LGR_FLAG=SET;
                    VCP.print("SD Ready to receive data.\r\n\r\n");                                    
                    break;
                }                    
            }
            if(!SD_LOG_TMR)
            {
                VCP.print("SD Error or No card.\r\n");                
                PMIC.setEXTEN(EXT_5V_OFF);
            }
        }
    }    
}

//─────────────────────────────────────────────────────────────────────────────

//─────────────────────── DEFAULT SCREEN INITIALIZATION ───────────────────────

if(!SKIP_INIT)
{   PMIC.setLDO2(LCD_BL_DIM);   }

if(SKIP_INIT)
{
    LCD.begin();
    delay(500);
    LCD.setRotation(1);
    PMIC.setLDO2(LCD_BL_OFF);   
    LED_EN_FLAG=CLEAR;
    LCD_BL_EN_FLAG=SET;
    LCD_ON_TMR=CLEAR;     
}    
    SYS_ACT_TMR=SYS_ACT_TME;
    SYS_PWR_ON_FLAG=CLEAR;   
    LCD_ON_TMR=LCD_ON_TME;
    SAL_DSP_FLAG=SET;
    PWR_DSP_FLAG=CLEAR;
    SKIP_INIT=CLEAR;

//─────────────────────────────────────────────────────────────────────────────

}

/*END OF FILE*/
