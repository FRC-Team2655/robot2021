/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class RotateDegreesCommand
    : public frc2::CommandHelper<frc2::CommandBase, RotateDegreesCommand> {
 public:
  RotateDegreesCommand(double degrees);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  /* Maximum speed to run at while turning (motor perent) */
  double maxSpeed = 0.25;
  /* Minimum speed to run while turning (motor percent) */
  double minSpeed = 0.05;
  /* delta from target angle at which to start ramp down (degrees) */
  double rampdownStartAngle = 15;
  /* P term for gyro feedback while ramping down */
  double P_gyro = 0.09;
  /* ramp up increment */
  double rampUpIncrement = 0.01;
  /* degrees to turn by */
  double degrees;
private:
  /* Start angle for the robot */
  double startAngle;
  /*Target angle to reach*/
  double targetAngle;
  /* Track if need to turn right or not */
  bool turnRight;
  /* current robot angle */
  double currentAngle;
  /* Current motor speed (RPM) */
  double currentSpeed;
};
