/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RunSideBeltsCommand.h"
#include "Robot.h"

RunSideBeltsCommand::RunSideBeltsCommand() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void RunSideBeltsCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RunSideBeltsCommand::Execute() {
  Robot::belts.runSideBelts();
}

// Called once the command ends or is interrupted.
void RunSideBeltsCommand::End(bool interrupted) {
  Robot::belts.stopBelts();
}

// Returns true when the command should end.
bool RunSideBeltsCommand::IsFinished() { return false; }
