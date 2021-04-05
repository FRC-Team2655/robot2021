/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RunBeltsInvertedCommand.h"
#include "Robot.h"

RunBeltsInvertedCommand::RunBeltsInvertedCommand(double speed) : speed(speed) {
  AddRequirements(&Robot::belts);
}

// Called when the command is initially scheduled.
void RunBeltsInvertedCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RunBeltsInvertedCommand::Execute() {
  Robot::belts.runBeltsInverted(speed);
}

// Called once the command ends or is interrupted.
void RunBeltsInvertedCommand::End(bool interrupted) {
  Robot::belts.stopBelts();
}

// Returns true when the command should end.
bool RunBeltsInvertedCommand::IsFinished() { return false; }
