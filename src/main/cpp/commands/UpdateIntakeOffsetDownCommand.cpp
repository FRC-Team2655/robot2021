/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/UpdateIntakeOffsetDownCommand.h"
#include "Robot.h"

UpdateIntakeOffsetDownCommand::UpdateIntakeOffsetDownCommand() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void UpdateIntakeOffsetDownCommand::Initialize() {
  Robot::intake.updateOffsetDown();
}

// Called repeatedly when this Command is scheduled to run
void UpdateIntakeOffsetDownCommand::Execute() {}

// Called once the command ends or is interrupted.
void UpdateIntakeOffsetDownCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool UpdateIntakeOffsetDownCommand::IsFinished() { return true; }
