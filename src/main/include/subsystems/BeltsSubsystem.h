/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include "RobotMap.h"
#include <ctre/Phoenix.h>
#include <frc/DigitalInput.h>

class BeltsSubsystem : public frc2::SubsystemBase {
 public:
  BeltsSubsystem();

  void runBelts(double speed, bool useProximitySensor);
  void stopBelts();

  void runSideBelts();
  void runBottomBelt();
  void runKickerBelt();

  void setCoastMode();

  bool isProximSensorTopTriggered();
  bool isProximSensorMiddleTriggered();
  bool isProximSensorBottomTriggered();

  void runBeltsSpeeds(double sides, double bottom, double kicker);
  void runBeltsInverted(double speed);

  void runAllBelts(double speed);

  int getBeltsState();

  void Periodic();

  bool shouldRunBelts = true;

 private:

  #if PRACTICEBOT
  WPI_VictorSPX bottomBelt {BeltBottom};
  WPI_TalonSRX kicker {KickerID};
  WPI_VictorSPX sideBelts {SideBelts};
  #else
  WPI_TalonSRX bottomBelt {BeltBottom};
  WPI_TalonSRX kicker {KickerID};
  WPI_TalonSRX leftBelt {BeltLeft};
  WPI_TalonSRX rightBelt {BeltRight};
  #endif

  frc::DigitalInput proximSensorTop {proximitySensorTopChannel};
  frc::DigitalInput proximSensorMiddle {proximitySensorMiddleChannel};
  frc::DigitalInput proximSensorBottom {proximitySensorBottomChannel};
};