/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveJoystickCommand.h"
#include "Robot.h"

DriveJoystickCommand::DriveJoystickCommand() {
  AddRequirements(&Robot::driveBase);
}

// Called when the command is initially scheduled.
void DriveJoystickCommand::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void DriveJoystickCommand::Execute() {
  #if MITHOONDRIVE
  double rawForward = (Robot::oi.js0->GetRawAxis(3) + 1) / 2;
  double rawBackward = (Robot::oi.js0->GetRawAxis(4) + 1) / 2;
  double deadband = 0.1;
  double driveDirection;

  if (rawForward > deadband && rawBackward > deadband) driveDirection = 0;
  else if (rawForward > deadband) driveDirection = rawForward;
  else if (rawBackward > deadband) driveDirection = -rawBackward;


  double rotate = -0.5 * jshelper::getAxisValue(Robot::oi.rotateAxisConfig, Robot::oi.js0->GetRawAxis(0));
  double power = jshelper::getAxisValue(Robot::oi.driveAxisConfig, driveDirection);

	Robot::driveBase.driveVelocity(power, rotate);

  #else

  double power = jshelper::getAxisValue(Robot::oi.driveAxisConfig, Robot::oi.js0->GetRawAxis(1));
	double rotate = -0.4 * jshelper::getAxisValue(Robot::oi.rotateAxisConfig, Robot::oi.js0->GetRawAxis(2));
  #endif
}

// Called once the command ends or is interrupted.
void DriveJoystickCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool DriveJoystickCommand::IsFinished() { return false; }
