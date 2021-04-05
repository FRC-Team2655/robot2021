/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/IntakeArmLockPIDCommand.h"
#include "Robot.h"

IntakeArmLockPIDCommand::IntakeArmLockPIDCommand() {
  AddRequirements(&Robot::intake);
}

// Called when the command is initially scheduled.
void IntakeArmLockPIDCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void IntakeArmLockPIDCommand::Execute() {
  Robot::intake.setLockPID();
  std::cout << "Arm Lock" << std::endl;
}

// Called once the command ends or is interrupted.
void IntakeArmLockPIDCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool IntakeArmLockPIDCommand::IsFinished() { return Robot::intake.isIntakeOut; }
