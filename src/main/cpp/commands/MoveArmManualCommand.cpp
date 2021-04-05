/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MoveArmManualCommand.h"
#include "Robot.h"

MoveArmManualCommand::MoveArmManualCommand() {
  AddRequirements(&Robot::intake);
}

// Called when the command is initially scheduled.
void MoveArmManualCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void MoveArmManualCommand::Execute() {
  Robot::intake.moveArmManual();
}

// Called once the command ends or is interrupted.
void MoveArmManualCommand::End(bool interrupted) {
  Robot::intake.stopArm();
}

// Returns true when the command should end.
bool MoveArmManualCommand::IsFinished() { return false; }
