/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/LEDSubsystem.h"

LEDSubsystem::LEDSubsystem() {
    /* Want to set up spark motor controller in constructor */
}

void LEDSubsystem::setLEDColor(LEDSubsystem::LEDColors color)
{
    /* Validate input */
    if(color >= LEDSubsystem::LEDColors::LED_COLOR_COUNT)
    {
        color = (LEDSubsystem::LEDColors) 0;
    }
    double LEDPower = 0.57;
    /* Doing some scuffed math here*/
    LEDPower += (0.02) * (double) color;
    /* Apply value to controller */
    LEDController.Set(LEDPower);
    /* Save seting */
    currentColor = color;
}

LEDSubsystem::LEDColors LEDSubsystem::getLEDColor()
{
    return currentColor;
}

void LEDSubsystem::setDualColorMode()
{
    /* Dual colors, wave mode */
    LEDController.Set(0.53);
}


// This method will be called once per scheduler run
void LEDSubsystem::Periodic() {}
