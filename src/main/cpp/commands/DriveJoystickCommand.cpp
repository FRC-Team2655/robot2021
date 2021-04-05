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
  double power = -1 * jshelper::getAxisValue(Robot::oi.driveAxisConfig, Robot::oi.js0->GetRawAxis(1));
	double rotate = .4 * jshelper::getAxisValue(Robot::oi.rotateAxisConfig, Robot::oi.js0->GetRawAxis(2));

	Robot::driveBase.driveVelocity(power, rotate);
}

// Called once the command ends or is interrupted.
void DriveJoystickCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool DriveJoystickCommand::IsFinished() { return false; }
