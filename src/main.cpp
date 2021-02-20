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
    File:       Main.c                -Main Looping code.
    Software:   0121400               -Software number.
    Board:      M5Stick-C Plus        -Color Display, WiFi, Bluetooth, Three switchs, Red & Ir LEDs, IMU, PMU, RTC, Various I/O.
                                       will include an external 18650 Hat, and a proto Hat with the µSD data logger.  Interface
                                       to the Salutron will be through the "GROVE" header.

    Software Supplement: 0121800 REV-1.0.0.XLS.     (Yet to Be Created)
    
───────────────────────── REVISION RECORD ───────────────────────────
    
    02/03/21    0121400-REV-1.0.2.
                -Initial Software build.  Goal is to connect the
                 Salutron to the M5Stick-C board and measure both
                 contact and wireless heart rate and display
                 the value on the OLED.  The RED LED will flash at 
                 the current heart rate.  Write the event to the
                 SD card until the events halt.  The IMU will look
                 for any motion on the machine and ignore the 
                 event recording until the unit is stable.
    
    02/06/21    0121400-REV-1.0.3.                 
                -This version will have deep sleep enabled.  When
                 the unit does not see any activity after a predetermined
                 time, the unit will shut off ALL perphials and enter
                 deep sleep.  The opposite is turn upon wake up.

    02/18/21    0121400-REV-1.0.4.                 
                -This version will have the ability to use the IMU to
                 determine if a person is using the equipment.  Upon 
                 initial Power-up after the device is mounted and secure,
                 the IMU is calibrated to it's final position.  If the
                 salutron wakes the unit, the software checks for motion.
                 If motion exists, the unit goes back to sleep an sets
                 the unit to be woke after 20 minutes to check to see
                 if motion still exists.  If not, the periodic wakeup
                 time is set back to 60 minutes, and the Salutron pulse
                 input is re-enabled to allow the sPulse line to wake
                 the unit from deepsleep.  Only further additions would
                 be communication via Blutooth.
                 

─────────────────────────────────────────────────────────────────────
*/

#include  "Globals.h"

void loop(void)
{
  do 
  {

//─────────────────────────────────────────────────────────────────────────────    
// CHECK VARIOUS FUNCTION:    Check Button, Change/update current selected screen.
//─────────────────────────────────────────────────────────────────────────────    

    if(MotionCheck())
    {   LPM_ShutDown();  }
    ButtonCheck();                              // Check the Push Buttons.
    BackLightControl();                         // See if BackLight need to be changed.
    DisplayPowerMonitor();                      // See if the Power-Monitor screen is to be Displayed.
    DisplaySalutron();                          // See if the Salutron screen is to be Displayed.

//─────────────────────────────────────────────────────────────────────────────    
// SD CARD LOGGING:   Writting the data to the SD Card.
//─────────────────────────────────────────────────────────────────────────────    

    if(SAL_SIG_DET)
    {
      Calculate_HR();                           // Calculate the current Heart-Rate.
      VCP_DataUpdate();                         // Update the VCP data.
      DataLoggerUpdate();                       // Update the Data-Logger.
    }

//─────────────────────────────────────────────────────────────────────────────    
// DEEPSLEEP CHECK:   Check to see if it's time to sleep.
//─────────────────────────────────────────────────────────────────────────────    

    if(!SYS_ACT_TMR)                            // Check to see if the SYStem-ACTivity-TiMeR is CLEAR.
    {   LPM_ShutDown();  }                      // If so, put the device into deep-sleep.
  } while(!digitalRead(SAL_PULSE));             // Wait for the Salutron sPulse line to go low.
  delay(40);                                    // Wait a bit before looping.
}
/*END OF FILE */