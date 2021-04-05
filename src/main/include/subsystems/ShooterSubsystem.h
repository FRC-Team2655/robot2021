#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include "RobotMap.h"
#include <ctre/Phoenix.h>
#include <frc/Timer.h>

#include <frc/DigitalInput.h>

using MotorType = rev::CANSparkMax::MotorType;

class ShooterSubsystem : public frc2::SubsystemBase {
 public:
  ShooterSubsystem();

  void runShooterPercentage(double speed);
  void runShooterVelocity();
  void setCoastMode();
  void stopShooter();

  double getShooter1Current();
  double getShooter1AccumError();

  double getRPM();

  void Periodic();

  double getAvgCurrent();

  rev::CANPIDController shooter1PID = shooter1.GetPIDController();

  #if COMPBOT
  double kP = 0.00001; 
  double kI = 0; 
  double kD = 0; 
  double kFF = 0.0005;
  #else
  double kP = 0.0000001; 
  double kI = 0; 
  double kD = 0; 
  double kFF = 0.000176;
  #endif

  bool isShooterAtMax = false;
  bool isShooterRunning = false;

 private:
  rev::CANSparkMax shooter1 {Shooter1ID, MotorType::kBrushless};
  rev::CANSparkMax shooter2 {Shooter2ID, MotorType::kBrushless};

  rev::CANEncoder shooterEncoder1 = shooter1.GetEncoder();

  double shooterSpeed;

  double kIz = 0;
  double kMax = 1;
  double kMin = 0;
};