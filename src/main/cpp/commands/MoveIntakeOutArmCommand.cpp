/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MoveIntakeOutArmCommand.h"
#include "Robot.h"
#include "RobotMap.h"

MoveIntakeOutArmCommand::MoveIntakeOutArmCommand(double position) : position(position) {
  AddRequirements(&Robot::intake);
}

// Called when the command is initially scheduled.
void MoveIntakeOutArmCommand::Initialize() {
  Robot::intake.setArmCoastMode();

  Robot::intake.isIntakeLocked = false;

  Robot::intake.setCurrent40();

  Robot::intake.intakeOutPID.SetSetpoint(position);
  Robot::intake.intakeOutPID.SetTolerance(armTolerance);
}

// Called repeatedly when this Command is scheduled to run
void MoveIntakeOutArmCommand::Execute() {
  Robot::intake.moveArmOut();
  std::cout << "Arm Out" << std::endl;
}

// Called once the command ends or is interrupted.
void MoveIntakeOutArmCommand::End(bool interrupted) {
  Robot::intake.stopArm();

  Robot::intake.setCurrent(armRestCurrent);
  Robot::intake.isIntakeOut = true;

  Robot::intake.setArmBrakeMode();
}

// Returns true when the command should end.
bool MoveIntakeOutArmCommand::IsFinished() {  
  return ((Robot::intake.armPosition() <= intakeOutPosition) || Robot::intake.intakeOutPID.AtSetpoint());
}
