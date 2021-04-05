/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RunIntakeRollersCommand.h"
#include "Robot.h"

RunIntakeRollersCommand::RunIntakeRollersCommand(double speed) : speed(speed) {
}

// Called when the command is initially scheduled.
void RunIntakeRollersCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RunIntakeRollersCommand::Execute() {
  Robot::intake.runRollers(speed);
}

// Called once the command ends or is interrupted.
void RunIntakeRollersCommand::End(bool interrupted) {
  Robot::intake.stopRollers();
}

// Returns true when the command should end.
bool RunIntakeRollersCommand::IsFinished() { return false; }
