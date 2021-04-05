/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RunBeltsBackgroundCommand.h"
#include "Robot.h"

RunBeltsBackgroundCommand::RunBeltsBackgroundCommand(double speed) : speed(speed) {
  AddRequirements(&Robot::belts);
}

// Called when the command is initially scheduled.
void RunBeltsBackgroundCommand::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void RunBeltsBackgroundCommand::Execute() {
  if (Robot::belts.shouldRunBelts) {
    Robot::belts.runBelts(speed, true);
  }
}

// Called once the command ends or is interrupted.
void RunBeltsBackgroundCommand::End(bool interrupted) {
  Robot::belts.shouldRunBelts = true;
  Robot::belts.stopBelts();
}

// Returns true when the command should end.
bool RunBeltsBackgroundCommand::IsFinished() { return !Robot::intake.isIntakeOut; }
