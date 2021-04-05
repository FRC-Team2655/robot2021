/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveDistanceCommand.h"
#include "Robot.h"

/*DriveDistanceCommand::DriveDistanceCommand(double distance, double maxSpeed) : distance(distance), maxSpeed(maxSpeed) {
  AddRequirements(&Robot::driveBase);
}*/

DriveDistanceCommand::DriveDistanceCommand(double distance) : distance(distance) {
  AddRequirements(&Robot::driveBase);
  maxSpeed = 2500;
}

// Called when the command is initially scheduled.
void DriveDistanceCommand::Initialize() {
  Robot::driveBase.driveTankPercentage(0, 0);
  Robot::driveBase.resetEncoders();
  currentDistance = 0;
  currentSpeed = 0;
  gyroStartAngle = Robot::driveBase.getIMUAngle();
  gyroAngle = gyroStartAngle;
  /* Determine direction */
  goingForward = true;
  if(distance < 0)
    goingForward = false;
}

// Called repeatedly when this Command is scheduled to run
void DriveDistanceCommand::Execute() {
  double remainingDistance;
  double gyroError, gyroSpeedCompensation;
  double leftSpeed, rightSpeed;

  //get travelled distance from encoders
  currentDistance = GetCurrentDistance();
  //calculate remaining distance (absolute value)
  remainingDistance = std::abs(distance - currentDistance);

  if(remainingDistance < rampDownDistance)
  {
    /* Slowing down. Want to go from maxspeed to 0 over 1 meter */
    currentSpeed -= (P_encoders * (rampDownDistance - remainingDistance));
    if(currentSpeed < minSpeed)
      currentSpeed = minSpeed;
  }
  else
  {
    /* Ramping up speed */
    if(currentSpeed < minSpeed)
    {
      currentSpeed = minSpeed;
    }
    else if(currentSpeed < maxSpeed)
    {
      currentSpeed += speedStep;
    }
    else
    {
      currentSpeed = maxSpeed;
    }
  }
  
  /* handle gyro compensation */

  /* Resample the gyro */
  gyroAngle = Robot::driveBase.getIMUAngle();

  /* Calculate the error (in degrees) */
  gyroError = gyroAngle - gyroStartAngle;
  
  /* Set gyro speed compensation value (gyro P term * error) */
  gyroSpeedCompensation = (P_gyro * gyroError);

  /* Apply gyro compensation */
  if(goingForward)
  {
    leftSpeed = currentSpeed + gyroSpeedCompensation;
    rightSpeed = currentSpeed - gyroSpeedCompensation;
  }
  else
  {
    leftSpeed = currentSpeed - gyroSpeedCompensation;
    rightSpeed = currentSpeed + gyroSpeedCompensation;
  }

  /* Check speed capping */
  if(leftSpeed > maxSpeed)
  {
    rightSpeed *= (maxSpeed / leftSpeed);
    leftSpeed = maxSpeed;
  }
  if(rightSpeed > maxSpeed)
  {
    leftSpeed *= (maxSpeed / rightSpeed);
    rightSpeed = maxSpeed;
  }

  /* Apply to drive base (update velocity set point) */
  if(goingForward)
      Robot::driveBase.driveTankVelocity(leftSpeed, rightSpeed);
  else
      Robot::driveBase.driveTankVelocity(-leftSpeed, -rightSpeed);

  std::cout << "Left: " << leftSpeed << ", " << "Right: " << rightSpeed << ", " << "Gyro Error: " << gyroError << std::endl;
}

// Called once the command ends or is interrupted.
void DriveDistanceCommand::End(bool interrupted) {
  Robot::driveBase.driveTankVelocity(0, 0);
}

// Returns true when the command should end.
bool DriveDistanceCommand::IsFinished() {
  if(goingForward)
    return currentDistance >= distance;
  else
    return currentDistance <= distance;
 }

 double DriveDistanceCommand::GetCurrentDistance()
 {
   double averageRotations;
   averageRotations = Robot::driveBase.getRightEncoderRotations() + Robot::driveBase.getLeftEncoderRotations();
   averageRotations *= 0.5;
   //scale to meters. Wheels are 6" (15cm) diameter
   return averageRotations * 3.141592 * 0.1524;
 }

double DriveDistanceCommand::inchesToMeters(double inches) {
  return inches / 39.37;
}