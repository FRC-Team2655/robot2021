/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "frc/Spark.h"
#include "RobotMap.h"

class LEDSubsystem : public frc2::SubsystemBase {
 public:

  /* Possible LED colors */
  typedef enum LEDColors{
    HotPink = 0,
    DarkRed,
    Red,
    RedOrange,
    Orange,
    Gold,
    Yellow,
    LawnGreen,
    Lime,
    DarkGreen,
    Green,
    BlueGreen,
    Aqua,
    SkyBlue,
    DarkBlue,
    Blue,
    BlueViolet,
    Violet,
    White,
    Gray,
    DarkGray,
    Black,
    LED_COLOR_COUNT,
    LED_DUAL_COLOR_MODE
  }LEDColors;

  LEDSubsystem();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  /* Set LEDS to a solid color */
  void setLEDColor(LEDColors color);

  /* Get the current LED color setting*/
  LEDColors getLEDColor();

  /* Set dual pattern idle mode (purple + gold)*/
  void setDualColorMode();

 private:
  frc::Spark LEDController {LEDPWMPort};
  LEDColors currentColor;
};
