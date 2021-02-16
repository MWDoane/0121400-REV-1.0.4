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
    File:       ISR.cpp               -Interrupt-Service-Routine functions.
    Software:   0121400               -Software number.
    Board:      M5Stick-C Plus        -Color Display, WiFi, Bluetooth, Three switchs, Red & Ir LEDs, IMU, PMU, RTC, Various I/O.
                                       will include an external 18650 Hat, and a proto Hat with the µSD data logger.  Interface
                                       to the Salutron will be through the "GROVE" header.

    Software Supplement: 0121800 REV-1.0.0.XLS.     (Yet to Be Created)
    
───────────────────────── REVISION RECORD ───────────────────────────
    
    ***** SEE 0121400-REV-X.X.X main.cpp FOR REVISION DETAILS *****

─────────────────────────────────────────────────────────────────────
*/

#include    "ISR.h"

/*
───────────────────────────────────────────────────────────────────────────────
SALutron-ChecK-ISR  Rising edge has been detected on the SAL_PULSE line.
                    Set the STOP-TiME to current time in µS. Set the ELAPSED-
                    TiME to the STOP-TiME - START-TiME.  Set the START-TiME
                    to current time.

Arguments:      None.
Returns:        Nothing.

───────────────────────────────────────────────────────────────────────────────
*/

void    IRAM_ATTR SAL_CHK_ISR(void)
{
    portENTER_CRITICAL(&GPIO_SYNC);
    sPULSE_STOP_TME=micros();
    sPULSE_ELAPSED_TME=(sPULSE_STOP_TME-sPULSE_START_TME);    
    sPULSE_START_TME=micros();
    if(LED_EN_FLAG)
    {
        pinMode(RED_LED,OUTPUT);
        digitalWrite(RED_LED,LOW);
        LED_ON_TMR=LED_ON_TME;
    }
    CRNT_PULSE_CNT++;
    SAL_SIG_DET=SET;
    SYS_ACT_TMR=SYS_ACT_TME;
    portEXIT_CRITICAL(&GPIO_SYNC);    
    return;
}

/*
───────────────────────────────────────────────────────────────────────────────
BuTtoN-ChecK-ISR    CHecKs for when the M5 push BuTtoN is pressed, then CLEAR's
                    out the current and previous count registers.

Arguments:      None.
Returns:        Nothing.

───────────────────────────────────────────────────────────────────────────────
*/

void    IRAM_ATTR BTN_CHK_ISR(void)
{   
    portENTER_CRITICAL(&GPIO_SYNC);

    if(!PBTN_DB_TMR)
    {
        PBTN_DET_FLAG=SET;
/*
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
                        String EventCount=String(CRNT_PULSE_CNT);            
                        LCD.drawString(EventCount+"     ",175,61,2);   
                    }
                }
            }
        }

        if(TOP_PB)
        {
            if(LCD_BL_EN_FLAG)
            {        
                if(SAL_DSP_FLAG)
                {
                    SAL_DSP_FLAG=CLEAR;
                    PWR_DSP_FLAG=SET;
                }
                else if(PWR_DSP_FLAG)
                {
                    SAL_DSP_FLAG=SET;
                    PWR_DSP_FLAG=CLEAR;
                }
            }
        DSP_SET_FLAG=CLEAR;
        }
*/        
        PBTN_DB_TMR=PBTN_DB_TME;
        LCD_ON_TMR=LCD_ON_TME;        
        SYS_ACT_TMR=SYS_ACT_TME;        
    }

    portEXIT_CRITICAL(&GPIO_SYNC);        
    return;
}

/*
───────────────────────────────────────────────────────────────────────────────
SYStem-ChecK-ISR    A Falling edge has been detected on the SYS_INT line.
                    Determine the cause of the INTerrupt and take appropriate
                    actions.

Arguments:      None.
Returns:        Nothing.

───────────────────────────────────────────────────────────────────────────────
*/

void    IRAM_ATTR SYS_CHK_ISR(void)
{   
    portENTER_CRITICAL(&GPIO_SYNC);
    portEXIT_CRITICAL(&GPIO_SYNC);
    return;
}

/*
───────────────────────────────────────────────────────────────────────────────
TiMeR-ChecK-ISR     When the hardare timer fire an interrupt, the 1mS TiMeRs
                    are serviced.  All timers are count down.

Arguments:      None.
Returns:        Nothing.

───────────────────────────────────────────────────────────────────────────────
*/

void    IRAM_ATTR TMR_CHK_ISR(void)
{   
    portENTER_CRITICAL(&HW_TMR);

//────────────────────────── SERVICE LED-ON-TIMER ─────────────────────────────

    if(LED_ON_TMR!=CLEAR)
    {   LED_ON_TMR--;   }
    else
    {
        if(!digitalRead(RED_LED))
        {   
            digitalWrite(RED_LED,HIGH);
            pinMode(RED_LED,INPUT);
        }
    }

//─────────────────────────────────────────────────────────────────────────────

//─────────────────── SERVICE PUSH BUTTON DEBOUNCE-TIMER ──────────────────────

    if(PBTN_DB_TMR!=CLEAR)
    {   PBTN_DB_TMR--;   }

//─────────────────────────────────────────────────────────────────────────────

//────────────────────────── SERVICE µSD-LOG-TIMER ────────────────────────────

    if(SD_LOG_TMR!=CLEAR)
    {   SD_LOG_TMR--;   }

//─────────────────────────────────────────────────────────────────────────────

//────────────────────── SERVICE SALUTRON-SIGNAL-TIMER ────────────────────────

    if(sPULSE_HIGH_TME!=CLEAR)
    {   sPULSE_HIGH_TME--;   }

//─────────────────────────────────────────────────────────────────────────────

//─────────────────────── SERVICE DISPLAY-MODE-TIMER ──────────────────────────

    if(DSP_MODE_TMR!=CLEAR)
    {   DSP_MODE_TMR--;   }

//─────────────────────────────────────────────────────────────────────────────

//────────────────────── SERVICE SYSTEM-ACTIVITY-TIMER ────────────────────────

    if(SYS_ACT_TMR!=CLEAR)
    {   SYS_ACT_TMR--;   }

//─────────────────────────────────────────────────────────────────────────────

//────────────────────── SERVICE LCD-DISPLAY-ON-TIMER ─────────────────────────

    if(LCD_ON_TMR!=CLEAR)
    {   LCD_ON_TMR--;   }

//─────────────────────────────────────────────────────────────────────────────

    portEXIT_CRITICAL(&HW_TMR);
    return;
}

//─────────────────────────────────────────────────────────────────────────────

/* END OF FILE */