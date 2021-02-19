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
    File:       Unit.cpp              -Salutron-Phantom-Detecter Unit functions.
    Software:   0121400               -Software number.
    Board:      M5Stick-C Plus        -Color Display, WiFi, Bluetooth, Three switchs, Red & Ir LEDs, IMU, PMU, RTC, Various I/O.
                                       will include an external 18650 Hat, and a proto Hat with the µSD data logger.  Interface
                                       to the Salutron will be through the "GROVE" header.

    Software Supplement: 0121800 REV-1.0.0.XLS.     (Yet to Be Created)
    
───────────────────────── REVISION RECORD ───────────────────────────
    
    ***** SEE 0121400-REV-X.X.X main.cpp FOR REVISION DETAILS *****

─────────────────────────────────────────────────────────────────────
*/

#include    "Unit.h"


//─────────────────────────────────────────────────────────────────────────────
//                          DEVICE FUNCTIONS LIST
//─────────────────────────────────────────────────────────────────────────────
/*
    Calculate_HR:
    Button Check:
    BackLightControl:   
    Display Splash Screen:
    Display Salutron Screen:
    Display Power Monitor Screen:
    VCP Data Update:
    Data Logger Update:
    MotionCalibration:
    Motion Check:
    PMIC CLeaR IRQ
    PMIC Temp. Monitor control:
    PMIC OVeR-Temp. Monitor control:
    Low Power Wake Up:
    Low Power Shut Down:
*/

/*
───────────────────────────────────────────────────────────────────────────────
Calculate-HR    Calculates the Heart-Rate based on the value of SALutron ELAPSED
                Time.  This is equal to the period of the pulse train.

Arguments:      None.

Returns:        The Calculated Heart-Rate in BPM.
───────────────────────────────────────────────────────────────────────────────
*/

float    Calculate_HR(void)
{
      HR_Value=(sPULSE_ELAPSED_TME/1000);
      HR_Value=((1/HR_Value)*60000);
      if(HR_Value>255)
      { HR_Value=CLEAR; }
      return HR_Value;
}      

/*
───────────────────────────────────────────────────────────────────────────────
DisplaySplash   Display's the True Fitness logo and the device name, software
                version, and the date.
Arguments:      None.
Returns:        Nothing.
───────────────────────────────────────────────────────────────────────────────
*/

_Bool   ButtonCheck(void)
{
    if(PBTN_DET_FLAG)
    {
    
//──────────────────────────── FRONT-PUSH BUTTON ──────────────────────────────

        if(!LCD_BL_EN_FLAG)
        {           
            LCD_BL_EN_FLAG=CLEAR;
            LCD_ON_TMR=LCD_ON_TME;
            VCP.print("BackLight Enable\r\n");
            return CLEAR;
        }

        if(!PBTN_DB_TMR)
        {
            if(FRONT_PB)
            {
                if(LCD_BL_EN_FLAG)
                {
                    if(SAL_DSP_FLAG)
                    {
                        if(CRNT_PULSE_CNT)
                        {
                            CRNT_PULSE_CNT=CLEAR;  
                            PRVS_PULSE_CNT=CLEAR;
                            VCP.print("Clear Counter\r\n");                            
                            String _CRNT_PULSE_CNT=String(CRNT_PULSE_CNT);         
                            LCD.drawString(_CRNT_PULSE_CNT+"      ",175,61,2);
                            HR_Value=CLEAR;
                            DSP_SET_FLAG=CLEAR;    
                            PBTN_DET_FLAG=CLEAR;      
                            while(!FRONT_PB);
                            PBTN_DB_TMR=PBTN_DB_TME;
                            return CLEAR;                        
                        }
                    }
                }
            }

//───────────────────────────── TOP-PUSH BUTTON ───────────────────────────────

            if(TOP_PB)
            {
                if(!LCD_BL_EN_FLAG)
                {           
                    LCD_BL_EN_FLAG=CLEAR;
                    LCD_ON_TMR=LCD_ON_TME;
                    while(!TOP_PB);                                            
                    PBTN_DB_TMR=PBTN_DB_TME;
                    return CLEAR;
                }

                if(LCD_BL_EN_FLAG)
                {        
                    if(SAL_DSP_FLAG)
                    {
                        VCP.print("Power Display\r\n");                                                    
                        SAL_DSP_FLAG=CLEAR;
                        PWR_DSP_FLAG=SET;
                        DSP_SET_FLAG=CLEAR;
                        PBTN_DET_FLAG=CLEAR;
                        while(!TOP_PB);                        
                        PBTN_DB_TMR=PBTN_DB_TME;
                        return  CLEAR;
                    }
                    else if(PWR_DSP_FLAG)
                    {
                        VCP.print("Salutron Display\r\n");                                                                            
                        SAL_DSP_FLAG=SET;
                        PWR_DSP_FLAG=CLEAR;
                        DSP_SET_FLAG=CLEAR;
                        PBTN_DET_FLAG=CLEAR;
                        while(!TOP_PB);                                                
                        PBTN_DB_TMR=PBTN_DB_TME;
                        return  CLEAR;
                    }
                }
            }
        }
    }
return  CLEAR;    
}

/*
───────────────────────────────────────────────────────────────────────────────
BackLightControl    Controls the Display's backlight, the display's on time, and
                    which screen of the Display is to be shown.
Arguments:          None.
Returns:            Nothing.
───────────────────────────────────────────────────────────────────────────────
*/

void    BackLightControl(void)                     
{
    if(LCD_ON_TMR!=CLEAR)
    {
      if(LCD_BL_EN_FLAG==CLEAR)
      {
        VCP.print("BackLight ON\r\n");                                                              
        PMIC.setLDO3(2700);                         // added
        PMIC.setLDO2(LCD_BL_DIM);                
        LCD_BL_EN_FLAG=SET;                      
        LED_EN_FLAG=SET;                         
        return;
      }
    }    
    if(LCD_ON_TMR==CLEAR)                        
    {                                            
      if(LCD_BL_EN_FLAG==SET)                         
      {                                          
        VCP.print("BackLight OFF\r\n");                                                                        
        PMIC.setLDO3(OFF);                          // added
        PMIC.setLDO2(LCD_BL_OFF);              
        LCD_BL_EN_FLAG=CLEAR;                  
        LED_EN_FLAG=CLEAR;                     
        return;
      }
    }
    return;
}

/*
───────────────────────────────────────────────────────────────────────────────
DisplaySplash   Display's the True Fitness logo and the device name, software
                version, and the date.
Arguments:      None.
Returns:        Nothing.
───────────────────────────────────────────────────────────────────────────────
*/

void    DisplaySplash(void)
{
    if(!SKIP_INIT)
    {
        LCD.begin();
        delay(500);
        LCD.setRotation(1);
        PMIC.setLDO2(LCD_BL_BRT);
        LCD.pushImage(0, 0, logoWidth, logoHeight, (uint16_t *)TF_logo);
        LCD.setTextColor(YELLOW);
        VCP.println("Display Ready.");
        LCD.drawString("M5P-SPD  REV-1.0.3",5,80,4);  
        LCD.drawString(String(RTC_Date.Month)+"-"+ 
                       String(RTC_Date.Date)+"-" + 
                       String(RTC_Date.Year)+"  "+
                       String(RTC_Time.Hours)+":"+
                       String(RTC_Time.Minutes),5,105,4);

        delay(5000);                    
    }
    return;
}

/*
───────────────────────────────────────────────────────────────────────────────
DisplaySalutron Display's the Default screen showing Pulse Rate, number of
                counts, and the current mode of the Salutron.

Arguments:      None.
Returns:        Nothing.
───────────────────────────────────────────────────────────────────────────────
*/

void    DisplaySalutron(void)
{
    if(SAL_DSP_FLAG)
    {
        if(!DSP_MODE_TMR)
        {
            if(!DSP_SET_FLAG)    
            {
                LCD.pushImage(0, 0, logoWidth, logoHeight, (uint16_t *)SAL_SCR);
                LCD.setTextColor(WHITE,BLACK);
                DSP_SET_FLAG=SET;
            }
            if(NoSalutronInput)
            {
                if((PRVS_PULSE_CNT=CRNT_PULSE_CNT))
                {
                    if(SAL_SIG_DET)
                    {
                        HR_Value=CLEAR;
                        SAL_SIG_DET=CLEAR;
                        LCD.drawString(" --  ",175,30,2);
                        String EventCount=String(CRNT_PULSE_CNT);            
                        LCD.drawString(EventCount+" ",175,61,2);
                        LCD.drawString(" --     ",170,92,2);
                        CHR=CLEAR;  WHR=CLEAR;  
                    }
                }  
            }
            else if(SalutronContact)
            {
                SYS_ACT_TMR=SYS_ACT_TME;
                if(!CHR)
                {   
                    CHR=SET;  WHR=CLEAR;    
                }
            }
            else if(SalutronWireless)
            {
                SYS_ACT_TMR=SYS_ACT_TME;
                if(!WHR)
                {   
                    CHR=CLEAR;  WHR=SET;    
                }
            }
            String PulseRate=String(HR_Value,0);
            String EventCount=String(CRNT_PULSE_CNT);
            if(!(CRNT_PULSE_CNT>=(PRVS_PULSE_CNT+3)))
            {   LCD.drawString(" --  ",175,30,2);   }      
            if((CRNT_PULSE_CNT>=(PRVS_PULSE_CNT+3)))
            {   LCD.drawString(PulseRate+" ",175,30,2);     }
            LCD.drawString(EventCount+" ",175,61,2);
            if(WHR)                     {   LCD.drawString("Wireless",170,92,2);        }
            else if(CHR)                {   LCD.drawString("Contact",170,92,2);         }
            else if((!WHR) || (!CHR))   {   LCD.drawString(" --     ",170,92,2);        }
            DSP_MODE_TMR=DSP_MODE_TME; 
        }
    }
    return;
}

/*
───────────────────────────────────────────────────────────────────────────────
DisplayPowerMonitor Display's the Power Monitor screen showing Voltages and
                    current draw.  For dianostic data.

Arguments:      None.
Returns:        Nothing.
───────────────────────────────────────────────────────────────────────────────
*/

void DisplayPowerMonitor(void)
{
    if(SAL_DSP_FLAG)
    {  return; }

    if(!DSP_MODE_TMR)
    {
        if(!DSP_SET_FLAG)    
        {
          PMIC.setLDO2(LCD_BL_DIM);
          LCD.fillScreen(BLACK);        
          LCD.pushImage(0, 0, logoWidth, logoHeight, (uint16_t *)PMU_SCR);
          LCD.setTextColor(WHITE,BLACK);
          DSP_SET_FLAG=SET;
        }  
        BAT_LEVEL=map((PMIC.getBatteryVoltage()),3150,4150,119,18);
        BAT_LEVEL=constrain(BAT_LEVEL,BAT_LEVEL_MAX,BAT_LEVEL_MIN);
        BAT_BAR_COLOR=GREEN;
        if((120-BAT_LEVEL)<63)  {   BAT_BAR_COLOR=YELLOW;  }
        if((120-BAT_LEVEL)<33)  {   BAT_BAR_COLOR=RED;     }
        LCD.fillRoundRect(12,18,27,(BAT_LEVEL-18),3,BLACK);
        LCD.fillRoundRect(12,BAT_LEVEL,27,(120-BAT_LEVEL),3,BAT_BAR_COLOR);
        if(PMIC.getVbusVoltage()<=4300)
        {   LCD.drawString(String((PMIC.getBatteryDischargeCurrent()*1),1),57,70,2);  }
        if(PMIC.getVbusVoltage()>=4500)          
        {   LCD.drawString(String((PMIC.getBatteryChargeCurrent()*1),0),57,70,2);  }          
        LCD.drawString(String((PMIC.getApsVoltage()/1000),2),194,13,2);
        if((PMIC.getVbusVoltage()/1000)<1)
        {   LCD.drawString(String("0.00"),194,44,2);  }
        else if((PMIC.getVbusVoltage()/1000)>1)
        {   LCD.drawString(String((PMIC.getVbusVoltage()/1000),2),194,44,2);  }
        LCD.drawString(String((PMIC.getBatteryVoltage()/1000),2),57,43,2);
        LCD.drawString(String((((PMIC.getInternalTemperature()*9)/5)+32),1),194,75,2);
        LCD.drawString(String((PMIC.getAcinVolatge()/1000),2),194,106,2);
        LCD_ON_TMR=LCD_ON_TME;          
        DSP_MODE_TMR=DSP_MODE_TME;

    }
    return;
}

/*
───────────────────────────────────────────────────────────────────────────────
VCP_DataUpdate      Updates the data on the VCP to make sure it matches what is
                    written to the µSD Card.

Arguments:          None.

Returns:            Nothing.

───────────────────────────────────────────────────────────────────────────────
*/
void    VCP_DataUpdate(void)
{
    RTC.GetTime(&RTC_Time);
    RTC.GetData(&RTC_Date);
    if (RTC_Time.Seconds != PRVS_SECOND)
    {
        if(RTC_Date.Date != PRVS_DAY)
        {    
            VCP.print(String(RTC_Date.Month)+"-"+ 
                      String(RTC_Date.Date)+"-"+ 
                      String(RTC_Date.Year)+"\r\n");
        }              
        VCP.print(String(RTC_Time.Hours)+":");
        if (RTC_Time.Minutes < 10)
        {   VCP.print('0');     }
        VCP.print(String(RTC_Time.Minutes)+":");
        if (RTC_Time.Seconds < 10)
        {   VCP.print('0');     }
        VCP.print(String(RTC_Time.Seconds)+",");
        VCP.printf("%d,",(uint)HR_Value);
        VCP.printf("%d,",(uint)CRNT_PULSE_CNT);
        if(WHR)                 {   VCP.print("WHR\r\n");  }
        else if(CHR)            {   VCP.print("CHR\r\n");  }
        else if(!(WHR || CHR))  {   VCP.print("-\r\n");    }
    }        
    
    return;
}

/*
───────────────────────────────────────────────────────────────────────────────
DataLoggerUpdate    Checks to see if the time has changed since last log was
                    written.  Checks to see if a Salutron signal is detected.
                    If both conditions are meet, the contents are written to
                    the SD card.                      

Arguments:          None.

Returns:            Nothing.

───────────────────────────────────────────────────────────────────────────────
*/

void    DataLoggerUpdate(void)
{
    if (RTC_Time.Seconds != PRVS_SECOND)
    {
        if(RTC_Date.Date != PRVS_DAY)
        {
            SD_LGR.print(String(RTC_Date.Month)+"-"+ 
                         String(RTC_Date.Date)+"-"+ 
                         String(RTC_Date.Year)+"\r\n");

        PRVS_DAY=RTC_Date.Date;
        }
        SD_LGR.print(String(RTC_Time.Hours)+":");
        if (RTC_Time.Minutes < 10)
        {   SD_LGR.print("0");  }
        SD_LGR.print(String(RTC_Time.Minutes)+":");
        if (RTC_Time.Seconds < 10)
        {   SD_LGR.print("0");  }
        SD_LGR.print(String(RTC_Time.Seconds)+",");
        SD_LGR.printf("%d,",(uint)HR_Value);
        SD_LGR.printf("%d,",(uint)CRNT_PULSE_CNT);
        if(WHR)                 {   SD_LGR.print("WHR");    }
        else if(CHR)            {   SD_LGR.print("CHR");    }
        else if(!(WHR || CHR))  {   SD_LGR.print("-");      }
        SD_LGR.print("\r\n");
        RTC.GetTime(&RTC_Time);
        PRVS_SECOND=RTC_Time.Seconds;
    }  
    return;
}

/*
───────────────────────────────────────────────────────────────────────────────
IMU-Calibration     Upon final installation, and the device being secure to the
                    equipment's frame, the IMU will average 30 readings upon
                    the inital power up.  These will be saved and used as the
                    IMU's offset for motion detection.
Arguments:      None.

Returns:        Nothing.
───────────────────────────────────────────────────────────────────────────────
*/

void    IMU_Calibration(void)
{
    I2C.beginTransmission(IMU_ADR);
    I2C.write(IMU_ACCEL_CFG_1);
    I2C.requestFrom(IMU_ADR, 1);
    I2C_BFR[0]=I2C.read();
    I2C.endTransmission();      
    I2C_BFR[0]=I2C_BFR[0] & (~ACCEL_FS_SEL);
    I2C_BFR[0]=I2C_BFR[0] | (ACCEL_FS_2g);
    I2C.beginTransmission(IMU_ADR);
    I2C.write(IMU_ACCEL_CFG_1);
    I2C.write(I2C_BFR[0]);
    I2C.endTransmission();
    AVG_ACC_X=CLEAR;      
    AVG_ACC_Y=CLEAR;
    AVG_ACC_Z=CLEAR;
    IMU_DET_FLAG=CLEAR;
    uint8_t AVG_CNTR=10;
    
    do
    {
        IMU.getAccelData(&accX,&accY,&accZ);    
        AVG_ACC_X+=int(accX*100);
        AVG_ACC_Y+=int(accY*100);
        AVG_ACC_Z+=int(accZ*100);
        AVG_CNTR--;
        delay(125);
        VCP.print(".");
    }
    while(AVG_CNTR!=CLEAR);
    
    AVG_ACC_X/=11;
    AVG_ACC_Y/=11;
    AVG_ACC_Z/=11;
    VCP.print("\r\nIMU Calibrated and Ready: ");                
    VCP.printf("X:%d  Y:%d  Z:%d\r\n", (int)AVG_ACC_X, (int)AVG_ACC_Y, (int)AVG_ACC_Z);
    return;
}

/*
───────────────────────────────────────────────────────────────────────────────
MotionCheck     Determines if the Salutron input signal is from a person on the
                equpment, or a true phantom.  If motion is triggered, the unit
                goes back to sleep and wakes periodically to check to see if
                the motion is still active.

Arguments:      None.

Returns:        Motion State.  No Motion Detected=CLEAR, Motion Detected=SET.
───────────────────────────────────────────────────────────────────────────────
*/
_Bool    MotionCheck(void)
{
    if(SAL_SIG_DET)
    {
        IMU_DET_FLAG=CLEAR;
        PMIC.setGPIO0(IMU_PWR_ON);
        delay(25);
        IMU.Init();
        I2C.beginTransmission(IMU_ADR);
        I2C.write(IMU_ACCEL_CFG_1);
        I2C.requestFrom(IMU_ADR, 1);
        I2C_BFR[0]=I2C.read();
        I2C.endTransmission();      
        I2C_BFR[0]=I2C_BFR[0] & (~ACCEL_FS_SEL);
        I2C_BFR[0]=I2C_BFR[0] | (ACCEL_FS_2g);
        I2C.beginTransmission(IMU_ADR);
        I2C.write(IMU_ACCEL_CFG_1);
        I2C.write(I2C_BFR[0]);
        I2C.endTransmission();
        IMU_CHK_TMR=250;
        IMU_DET_FLAG=CLEAR;
        do
        {
            IMU.getAccelData(&accX,&accY,&accZ);    
            accX=(int(accX*100)-int(AVG_ACC_X));
            accY=(int(accY*100)-int(AVG_ACC_Y));        
            accZ=(int(accZ*100)-int(AVG_ACC_Z));        
            if((int(accX)>IMU_DET_THLD) || (int(accX)<(IMU_DET_THLD*-1)))
            {   IMU_DET_FLAG=SET;   }
            if((int(accY)>IMU_DET_THLD) || (int(accY)<(IMU_DET_THLD*-1)))
            {   IMU_DET_FLAG=SET;   }
            if((int(accZ)>IMU_DET_THLD) || (int(accZ)<(IMU_DET_THLD*-1)))
            {   IMU_DET_FLAG=SET;   }
            VCP.printf("X:%d  Y:%d  Z:%d   ", (int)accX, (int)accY, (int)accZ);
            VCP.println();
            delay(10);
        }
        while(IMU_CHK_TMR);
        PMIC.setGPIO0(IMU_PWR_OFF);
        if(IMU_DET_FLAG)
        {   VCP.print("Motion Detected!\r\n");      }
        else if(!IMU_DET_FLAG)
        {   VCP.print("No Motion Detected.\r\n");   }    
        return  IMU_DET_FLAG;
    }
    return  CLEAR;
}

/*
───────────────────────────────────────────────────────────────────────────────
PMIC-CLeaR-IRQ      CLeaRs out the IRQ's from PMIC such that the SYStem-INT
                    line is high and ready to receive an INTerrupt from the
                    IMU.

Arguments:          None.
Returns:            Nothing.

───────────────────────────────────────────────────────────────────────────────
*/

void    PMIC_CLR_IRQ(void)
{
    I2C.beginTransmission(PMIC_ADR);                            // CLEAR out all PMIC IRQ's.
    I2C.write(IRQ_1_STAT);
    I2C.write(CLEAR);
    I2C.write(CLEAR);
    I2C.write(CLEAR);
    I2C.write(CLEAR);
    I2C.endTransmission();
    return;
}

/*
───────────────────────────────────────────────────────────────────────────────
PMIC-TeMP-MoNiToR   Either Enables, or Disables the PMIC internal TeMPerature
                    MoNiToR.

Arguments:          State:  Enable=1, Disable=0.
Returns:            Nothing.

───────────────────────────────────────────────────────────────────────────────
*/

void    PMIC_TMP_MNTR(_Bool State)
{
    uint8_t Value;
    I2C.beginTransmission(PMIC_ADR);
    I2C.write(ADC_EN2_CTRL_REG);
    I2C.requestFrom(PMIC_ADR, 1);
    Value=I2C.read();
    I2C.endTransmission();    
    if(State)
    {
        Value=(Value & (~INT_TMP_MNTR_EN));
        Value=(Value | INT_TMP_MNTR_EN);
    }
    else if(!State)
    {
        Value=(Value & (~INT_TMP_MNTR_EN));
    }
    I2C.beginTransmission(PMIC_ADR);
    I2C.write(ADC_EN2_CTRL_REG);
    I2C.write(Value);
    I2C.endTransmission();
    return;
}

/*
───────────────────────────────────────────────────────────────────────────────
PMIC-OVT-MoNiToR    Either Enables, or Disables the PMIC internal OVer
                    Temperature-MoNiToR module.

Arguments:          State:  Enable=1, Disable=0.
Returns:            Nothing.

───────────────────────────────────────────────────────────────────────────────
*/

void    PMIC_OVT_MNTR(_Bool State)
{
    uint8_t Value;
    I2C.beginTransmission(PMIC_ADR);
    I2C.write(OVR_TMP_CTRL_REG);
    I2C.requestFrom(PMIC_ADR, 1);
    Value=I2C.read();
    I2C.endTransmission();        
    if(State)
    {
        Value=Value & (~OVR_TMP_EN);
    }   
    else if(!State)
    {
        Value=(Value & (~OVR_TMP_EN));
        Value=(Value | OVR_TMP_EN);
    }     
    I2C.beginTransmission(PMIC_ADR);
    I2C.write(OVR_TMP_CTRL_REG);
    I2C.write(Value);
    I2C.endTransmission();        
    return;
}


/*
───────────────────────────────────────────────────────────────────────────────
PMIC-RTC-BKUP-CHRG  Either Enables, or Disables the PMIC's RTC battery BacK-UP
                    charger. It also set the charging current when the charger
                    is enabled.

Arguments:          State:  Enable=1, Disable=0.
                    Level:  One of Four Different Charging currents: 50,100,200,
                    and 400µA.

Returns:            Nothing.

───────────────────────────────────────────────────────────────────────────────
*/
void    PMIC_RTC_BKUP_CHRG(_Bool State, uint8_t Level)
{
    uint8_t New_Value;
    I2C.beginTransmission(PMIC_ADR);
    I2C.write(BAT_BKUP_CTRL_REG);
    I2C.requestFrom(PMIC_ADR, 1);
    New_Value=I2C.read();
    I2C.endTransmission();    
    New_Value=(New_Value & (~BAT_BKUP_CHRG_EN));
    if(State)
    {   New_Value=(New_Value | (BAT_BKUP_CHRG_EN));    }
    else if(!State)
    {    New_Value=(New_Value & BAT_BKUP_CHRG_EN);     }
    I2C.beginTransmission(PMIC_ADR);
    I2C.write(BAT_BKUP_CTRL_REG);
    I2C.write(New_Value);    
    I2C.endTransmission();

    I2C.beginTransmission(PMIC_ADR);
    I2C.write(BAT_BKUP_CTRL_REG);
    I2C.requestFrom(PMIC_ADR, 1);
    New_Value=I2C.read();
    I2C.endTransmission();    
    switch (Level)
    {
    case BKUP_CHRG_50uA:
        {
            New_Value=(New_Value & (~BKUP_CHRG_CLEAR));
            New_Value=(New_Value | BKUP_CHRG_50uA);
            break;
        }
    case BKUP_CHRG_100uA:
        {
            New_Value=(New_Value & (~BKUP_CHRG_CLEAR));
            New_Value=(New_Value | BKUP_CHRG_100uA);
            break;
        }
    case BKUP_CHRG_200uA:
        {
            New_Value=(New_Value & (~BKUP_CHRG_CLEAR));
            New_Value=(New_Value | BKUP_CHRG_200uA);
            break;
        }
    case BKUP_CHRG_400uA:
        {
            New_Value=(New_Value & (~BKUP_CHRG_CLEAR));
            New_Value=(New_Value | BKUP_CHRG_400uA);
            break;
        }                        
    
    default:
        break;
    }
    I2C.beginTransmission(PMIC_ADR);
    I2C.write(BAT_BKUP_CTRL_REG);
    I2C.write(New_Value);    
    I2C.endTransmission();    
    return;
}

/*
───────────────────────────────────────────────────────────────────────────────
LPM-WakeUp  Determines the source of the Low-Power-Mode-Wake-Up and displays
            the information on the terminal.

Arguments:      None.

Returns:        Source of Wake-Up.
───────────────────────────────────────────────────────────────────────────────
*/

void    LPM_WakeUp(void)
{
    CRNT_PULSE_CNT=DS_CRNT_PULSE_CNT;
    PRVS_PULSE_CNT=DS_PRVS_PULSE_CNT;
    AVG_ACC_X=DS_ACC_X_CAL_VAL;
    AVG_ACC_Y=DS_ACC_Y_CAL_VAL;
    AVG_ACC_Z=DS_ACC_Z_CAL_VAL;
    SYS_ACT_TMR=SYS_ACT_TME;
/*
    uint8_t PMIC_IRQ_STAT3;
    PMIC_IRQ_STAT3=PMIC.getPekPress();
    if((PMIC_IRQ_STAT3 & (0b00000011))!=CLEAR)
    {   
        SYS_PWR_ON_FLAG=SET;
        GPIO_WAKE_UP_FLAG=CLEAR;
        TMR_WAKE_UP_FLAG=CLEAR;        
        return;
    }
*/
    esp_sleep_wakeup_cause_t WAKEUP_SOURCE;
    WAKEUP_SOURCE=esp_sleep_get_wakeup_cause();
    switch(WAKEUP_SOURCE)
    {
        case ESP_SLEEP_WAKEUP_EXT0:         
        {
            VCP.print("Salutron Wake-Up.\r\n\r\n");            
            GPIO_WAKE_UP_FLAG=SET;
            SKIP_INIT=SET;
            break;
        }

        case ESP_SLEEP_WAKEUP_EXT1:
        {
            VCP.print("Push-Button Wake-Up.\r\n\r\n");
            PBTN_WAKE_UP_FLAG=SET;
            SKIP_INIT=SET;            
            break;
        }

        case ESP_SLEEP_WAKEUP_TIMER:
        {
            VCP.print("Periodic Wake-Up.\r\n\r\n");
            TMR_WAKE_UP_FLAG=SET;
            SKIP_INIT=SET;            
            break;
        }

        case ESP_SLEEP_WAKEUP_ULP:
        {
            VCP.print("ULP Wake-Up.\r\n\r\n");            
            SKIP_INIT=SET;            
            break;
        }   

        default:                            
        {
            SKIP_INIT=CLEAR;            
            VCP.print("Power Button pressed.\r\n\r\n");
            break;
        }
    }
    I2C.begin(SDA,SCL);
    return;
}

/*
───────────────────────────────────────────────────────────────────────────────
LPM-ShutDown  Determines the source of the Low-Power-Mode-Wake-Up and displays
            the information on the terminal.

Arguments:      None.

Returns:        Nothing.
───────────────────────────────────────────────────────────────────────────────
*/

void    LPM_ShutDown(void)
{
    // Save these registers to RTC memory.
    DS_CRNT_PULSE_CNT=CRNT_PULSE_CNT;
    DS_PRVS_PULSE_CNT=PRVS_PULSE_CNT;
    DS_ACC_X_CAL_VAL=AVG_ACC_X;
    DS_ACC_Y_CAL_VAL=AVG_ACC_Y;
    DS_ACC_Z_CAL_VAL=AVG_ACC_Z;

    // Set these pins as inputs to reduce sleep current.
    pinMode(TXO_TO_LGR,INPUT);  
    pinMode(GPIO_5,INPUT);  
    pinMode(GPIO_13,INPUT);
    pinMode(GPIO_15,INPUT); 
    pinMode(GPIO_23,INPUT); 
    pinMode(GPIO_34,INPUT); 
    pinMode(SAL_PULSE,INPUT); 
    pinMode(SAL_MODE,INPUT);
    detachInterrupt(SAL_PULSE);
    if(IMU_DET_FLAG)  
    {
        esp_sleep_enable_timer_wakeup(SleepTime_S);
    }
    else if(!IMU_DET_FLAG)
    {
        esp_sleep_enable_timer_wakeup(SleepTime_L);
        esp_sleep_enable_ext0_wakeup(GPIO_NUM_32,LOW);
    }
//    esp_sleep_enable_ext1_wakeup(PBTN_F_WAKEUP,ESP_EXT1_WAKEUP_ALL_LOW);    // Wake if the Front Button is pressed.
    adc_power_off();

//─────────────────────────────── RTC ACTIONS ─────────────────────────────────
    
    //Turn off the RTC CLK Output.
    I2C.beginTransmission(RTC_ADR);
    I2C.write(CLKOUT_REG);    
    I2C.write(CLEAR);
    I2C.endTransmission();

//─────────────────────────────────────────────────────────────────────────────


//────────────────────────────── PMIC ACTIONS ─────────────────────────────────

    // Disable the TS pin on PMIC.
    I2C.beginTransmission(PMIC_ADR);
    I2C.write(ADC_SR_TS_CTRL_REG);
    I2C.requestFrom(PMIC_ADR, 1);
    I2C_BFR[0] = (I2C.read() & (~TS_PIN_CRNT));
    I2C.endTransmission();
    I2C.beginTransmission(PMIC_ADR);
    I2C.write(ADC_SR_TS_CTRL_REG);
    I2C.write(I2C_BFR[0]);
    I2C.endTransmission();

//─────────────────────────────────────────────────────────────────────────────

    // Disable GPIO's.
    PMIC.setGPIO0(IMU_PWR_OFF);
    PMIC.setGPIO1(GPIO_X_DISABLE);
    PMIC.setGPIO2(GPIO_X_DISABLE);

//─────────────────────────────────────────────────────────────────────────────

    // Disable Bat-BackUp.
    PMIC_RTC_BKUP_CHRG(DISABLE,BKUP_CHRG_DSABLE);

    // Just DCDC1 ON.
    I2C.beginTransmission(PMIC_ADR);
    I2C.write(DCDC_1_3_CTRL_REG);    
    I2C.write(DCDC_1_PWR_EN);
    I2C.endTransmission();        

    I2C.beginTransmission(PMIC_ADR);
    I2C.write(DCDC_2_CTRL_REG);    
    I2C.write(CLEAR);
    I2C.endTransmission();                

//─────────────────────────────────────────────────────────────────────────────

    // Disable all ADC.
    I2C.beginTransmission(PMIC_ADR);
    I2C.write(ADC_EN1_CTRL_REG);
    I2C.write(CLEAR);
    I2C.endTransmission();        

    // Disable Internal Temp. Monitor.
    PMIC_TMP_MNTR(DISABLE);              

    // Disable Over Temp. Monitor Module.
    PMIC_OVT_MNTR(DISABLE);                                     


//─────────────────────────────────────────────────────────────────────────────

    esp_sleep_pd_config(ESP_PD_DOMAIN_MAX,ESP_PD_OPTION_AUTO);
    VCP.print("\r\nEntering Deep Sleep...");
    delay(75);
    esp_deep_sleep_start();
    delay(100);    
    return;
}


/*END OF FILE*/