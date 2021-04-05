/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RunShooterVelocityCommand.h"
#include "Robot.h"

RunShooterVelocityCommand::RunShooterVelocityCommand() {
  AddRequirements(&Robot::shooter);
}

// Called when the command is initially scheduled.
void RunShooterVelocityCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RunShooterVelocityCommand::Execute() {
  Robot::shooter.runShooterVelocity();
}

// Called once the command ends or is interrupted.
void RunShooterVelocityCommand::End(bool interrupted) {
  Robot::shooter.stopShooter();
}

// Returns true when the command should end.
bool RunShooterVelocityCommand::IsFinished() { return false; }
