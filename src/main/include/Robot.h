/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>
#include "frc/Timer.h"

#include "subsystems/DriveBaseSubsystem.h"
#include "OI.h"
#include "commands/DriveJoystickCommand.h"
#include "subsystems/ShooterSubsystem.h"
#include "subsystems/IntakeSubsystem.h"
#include "subsystems/BeltsSubsystem.h"
#include "subsystems/LEDSubsystem.h"
#include "AutonomousRoutines.h"
#include <frc/SmartDashboard/SendableChooser.h>

class Robot : public frc::TimedRobot {
 public:
  static OI oi;
  static DriveBaseSubsystem driveBase;
  static ShooterSubsystem shooter;
  static IntakeSubsystem intake;
  static BeltsSubsystem belts;
  static LEDSubsystem leds;
  static AutonomousRoutines autoRoutines;

  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;
private:
  frc2::Command* autonomousCommand = nullptr;
  frc::SendableChooser<int> autoChooser;

  double autoDistance;
  double autoDegrees;
  double preloadStartOffset = 0;
  double autoStartDelayMs = 0;
  double penc, pgyro, rotatePGyro;
  int buddyDrive = 0;

  #if COMPBOT
  double kInP = 1.7; 
  #else
  double kInP = 1.0; 
  #endif
  double kInI = 0.0; 
  double kInD = 0.1;
  double kOutP = 0.83;
  double kOutI = 0.0;
  double kOutD = 0.005;
  double kLockP = 1.5;
  double kLockI = 0.001;
  double kLockD = 0.0;
};
