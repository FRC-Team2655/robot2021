/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include "RobotMap.h"
#include <rev/CANSparkMax.h>
#include <frc/DutyCycleEncoder.h>
#include <frc/DutyCycle.h>
#include <frc/controller/PIDController.h>
#include <frc/DigitalInput.h>

using MotorType = rev::CANSparkMax::MotorType;

class IntakeSubsystem : public frc2::SubsystemBase {
 public:
  IntakeSubsystem();
  void runRollers(double speed);
  void stopRollers();
  void stopArm();
  void setRollersCoastMode();
  void setArmBrakeMode();
  void setArmCoastMode();

  void moveArmIn();
  void moveArmOut();
  void moveArmManual();
  double armRawPosition();
  double armPosition();

  void updateOffset();
  void updateOffsetDown();

  void setCurrent(double current);
  void setCurrent40();

  void setLockPID();
  void setLockDownPID();
  void setInPID();

  double intakeArmCurrent();

  void resetArmEnc();

  void Periodic();

  double kVelocity_;

  #if COMPBOT
  double kP_ = 1.7;
  #else
  double kP_ = 1.0;
  #endif

  frc2::PIDController intakeInPID {kP_, 0, 0.1};
  frc2::PIDController intakeOutPID {1.0, 0, 0.005};
  frc2::PIDController intakeLockPID {1.5, 0.001, 0};
  frc2::PIDController intakeLockDownPID {0.83, 0.0001, 0};
  
  double intakePositionOffset;
  double intakeMotorValue = 0;

  bool isIntakeOut = false;
  bool isIntakeLocked = true;
private:
  WPI_TalonSRX intakeRollers {RollerShooters};
  rev::CANSparkMax intakeArm {IntakeArm, MotorType::kBrushless};

  //frc::DutyCycleEncoder intakeEnc {IntakePWM};
  frc::DutyCycle intakeEnc {new frc::DigitalInput(IntakePWM)};
};
