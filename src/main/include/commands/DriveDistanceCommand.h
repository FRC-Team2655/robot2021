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
class DriveDistanceCommand
    : public frc2::CommandHelper<frc2::CommandBase, DriveDistanceCommand> {
 public:
  //DriveDistanceCommand(double distance, double maxSpeed);
  DriveDistanceCommand(double distance);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  static double inchesToMeters(double inches);

  /* P term for P feedback loop from encoders */
  double P_encoders = 100.0;

  /* P term for P feedback loop from gyro for angle correction */
  double P_gyro = 85.0;

  /* Angle read from current axis of interest on the gyro */
  double gyroAngle;

  /* max speed during movement. In units of motor RPM (0 - 5800) */
  double maxSpeed;

private:

  double GetCurrentDistance();

  /* Initial starting angle from gyro */
  double gyroStartAngle;
  /* Target distance to travel */
  double distance;
  /* Current distance travelled */
  double currentDistance;
  /* Current "uncompensated" speed */
  double currentSpeed;
  /* min speed during movement. In units of motor RPM (0 - 5800) */
  double minSpeed = 1000;
  /* Amount to step up speed per iteration when accelerating */
  double speedStep = 85;
  /* distance to start ramp down PID (meters) */
  double rampDownDistance = 1.0;
  /* travel direction */
  bool goingForward;
};
