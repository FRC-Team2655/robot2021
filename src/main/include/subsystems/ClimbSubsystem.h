/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "RobotMap.h"
#include <rev/CANSparkMax.h>

using MotorType = rev::CANSparkMax::MotorType;

class ClimbSubsystem : public frc2::SubsystemBase {
 public:
  ClimbSubsystem();

  void Periodic();

 private:
  //rev::CANSparkMax climMotor1 {ClimbMotor1, MotorType::kBrushless};
  //rev::CANSparkMax climbMotor2 {ClimbMotor2, MotorType::kBrushless};
};
