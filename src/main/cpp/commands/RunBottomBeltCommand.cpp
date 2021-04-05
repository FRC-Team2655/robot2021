/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RunBottomBeltCommand.h"
#include "Robot.h"

RunBottomBeltCommand::RunBottomBeltCommand() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void RunBottomBeltCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RunBottomBeltCommand::Execute() {
  Robot::belts.runBottomBelt();
}

// Called once the command ends or is interrupted.
void RunBottomBeltCommand::End(bool interrupted) {
  Robot::belts.stopBelts();
}

// Returns true when the command should end.
bool RunBottomBeltCommand::IsFinished() { return false; }
