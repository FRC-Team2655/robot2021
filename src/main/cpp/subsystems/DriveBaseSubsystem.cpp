/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveBaseSubsystem.h"
#include "Robot.h"
#include <math.h>

using IdleMode = rev::CANSparkMax::IdleMode;

DriveBaseSubsystem::DriveBaseSubsystem() {
  imu.SetYawAxis(frc::ADIS16470_IMU::IMUAxis::kZ);

  leftSlave1.Follow(leftMaster);
  leftSlave2.Follow(leftMaster);
  rightSlave1.Follow(rightMaster);
  rightSlave2.Follow(rightMaster);

  leftPID.SetP(kPLeft);
  leftPID.SetI(kILeft);
  leftPID.SetD(0);
  leftPID.SetFF(1/LMaxVelocity);
  leftPID.SetIZone(0);
  leftPID.SetOutputRange(-1, 1);

  rightPID.SetP(kPRight);
  rightPID.SetI(kIRight);
  rightPID.SetD(0);
  rightPID.SetFF(1/RMaxVelocity);
  rightPID.SetIZone(0);
  rightPID.SetOutputRange(-1, 1);

  leftMaster.SetClosedLoopRampRate(DriveRampRate);
  rightMaster.SetClosedLoopRampRate(DriveRampRate);

  // Current limiting
  const int stallLimit = 38, freeLimit = 60, limitRPM = 2000;
  leftMaster.SetSmartCurrentLimit(stallLimit, freeLimit, limitRPM);
  leftSlave1.SetSmartCurrentLimit(stallLimit, freeLimit, limitRPM);
  leftSlave2.SetSmartCurrentLimit(stallLimit, freeLimit, limitRPM);
  rightMaster.SetSmartCurrentLimit(stallLimit, freeLimit, limitRPM);
  rightSlave1.SetSmartCurrentLimit(stallLimit, freeLimit, limitRPM);
  rightSlave2.SetSmartCurrentLimit(stallLimit, freeLimit, limitRPM);


  leftMaster.BurnFlash();
  leftSlave1.BurnFlash();
  leftSlave2.BurnFlash();
  rightMaster.BurnFlash();
  rightSlave1.BurnFlash();
  rightSlave2.BurnFlash();

  SetDefaultCommand(driveJoystick);

  //rightMaster.SetInverted(true);
  //leftMaster.SetInverted(false);
}

// This method will be called once per scheduler run
void DriveBaseSubsystem::Periodic() {
}

void DriveBaseSubsystem::resetIMUAngle()
{
	imu.Reset();
}

void DriveBaseSubsystem::drivePercentage(double speed, double rotation){
	std::array<double, 2> speeds = arcadeDrive(speed, rotation);
	driveTankPercentage(speeds[0], speeds[1]);
}

void DriveBaseSubsystem::driveTankPercentage(double leftPercentage, double rightPercentage) {
	leftMaster.Set(-leftPercentage);
	leftSlave1.Set(-leftPercentage);
	leftSlave2.Set(-leftPercentage);

	rightMaster.Set(rightPercentage);
	rightSlave1.Set(rightPercentage);
	rightSlave2.Set(rightPercentage);
}

std::array<double, 2> DriveBaseSubsystem::arcadeDrive(double xSpeed, double zRotation) {

	double leftMotorOutput;
	double rightMotorOutput;

	// Prevent -0 from breaking the arcade drive...
	xSpeed += 0.0;
	zRotation += 0.0;

	double maxInput = std::copysign(std::max(std::abs(xSpeed), std::abs(zRotation)), xSpeed);

	if (xSpeed >= 0.0) {
		// First quadrant, else second quadrant
		if (zRotation >= 0.0) {
			leftMotorOutput = maxInput;
			rightMotorOutput = xSpeed - zRotation;
		} else {
			leftMotorOutput = xSpeed + zRotation;
			rightMotorOutput = maxInput;
		}
	} else {
		// Third quadrant, else fourth quadrant
		if (zRotation >= 0.0) {
			leftMotorOutput = xSpeed + zRotation;
			rightMotorOutput = maxInput;
		} else {
			leftMotorOutput = maxInput;
			rightMotorOutput = xSpeed - zRotation;
		}
	}

	return { leftMotorOutput, rightMotorOutput };
}

void DriveBaseSubsystem::driveVelocity(double speed, double rotation) {
	std::array<double, 2> speeds = arcadeDrive(speed, rotation);
	speeds[0] *= MaxVelocity;
	speeds[1] *= MaxVelocity;
	driveTankVelocity(speeds[0], speeds[1]);
}

void DriveBaseSubsystem::driveTankVelocity(double lVel, double rVel) {
	if (lVel == 0) {
		// If target velocity is 0 do not use PID to get to 0 just cut power (0%)
		leftMaster.Set(0);
	}else {
		// Drive the left side in velocity closed loop mode (set pid reference = setpoint for PID)
		leftPID.SetReference(-lVel, rev::ControlType::kVelocity);
	}

	if (rVel == 0) {
		rightMaster.Set(0);
	}
	
	else {
		rightPID.SetReference(rVel, rev::ControlType::kVelocity);
	}
}

void DriveBaseSubsystem::setBrakeMode() {
	leftMaster.SetIdleMode(IdleMode::kBrake);
	leftSlave1.SetIdleMode(IdleMode::kBrake);
	leftSlave2.SetIdleMode(IdleMode::kBrake);

	rightMaster.SetIdleMode(IdleMode::kBrake);
	rightSlave1.SetIdleMode(IdleMode::kBrake);
	rightSlave2.SetIdleMode(IdleMode::kBrake);
}

void DriveBaseSubsystem::setCoastMode() {
	leftMaster.SetIdleMode(IdleMode::kCoast);
	leftSlave1.SetIdleMode(IdleMode::kCoast);
	leftSlave2.SetIdleMode(IdleMode::kCoast);

	rightMaster.SetIdleMode(IdleMode::kCoast);
	rightSlave1.SetIdleMode(IdleMode::kCoast);
	rightSlave2.SetIdleMode(IdleMode::kCoast);
}

double DriveBaseSubsystem::getLeftEncoderRotations() {
	return (leftAutoEncoder.GetRaw() / 8192.0);
}

double DriveBaseSubsystem::getRightEncoderRotations() {
	return (-1 * (rightAutoEncoder.GetRaw() / 8192.0));
}

double DriveBaseSubsystem::getRightEncoderRate() {
	return leftAutoEncoder.GetRate();
}

double DriveBaseSubsystem::getLeftEncoderRate() {
	return rightAutoEncoder.GetRate();
}

frc::DifferentialDriveWheelSpeeds DriveBaseSubsystem::getEncoderOutputs() {
	return {units::meters_per_second_t(leftAutoEncoder.GetRate()),
			units::meters_per_second_t(rightAutoEncoder.GetRate())};
}

void DriveBaseSubsystem::tankDriveVolts(units::volt_t left, units::volt_t right) {
	leftMaster.SetVoltage(left);
	leftSlave1.SetVoltage(left);
	leftSlave2.SetVoltage(left);
	rightMaster.SetVoltage(-right);
	rightSlave1.SetVoltage(-right);
	rightSlave2.SetVoltage(-right);
}

void DriveBaseSubsystem::resetEncoders() {
	leftAutoEncoder.Reset();
	rightAutoEncoder.Reset();
}

frc::Rotation2d DriveBaseSubsystem::getAutoIMUAngle() {
	return frc::Rotation2d((units::radian_t)(imu.GetAngle() * 3.141592 / 180.0));
}

double DriveBaseSubsystem::getIMUAngle() {
	return imu.GetAngle();
}

double DriveBaseSubsystem::leftCurrent() {
	return leftMaster.GetOutputCurrent();
}

double DriveBaseSubsystem::rightCurrent() {
	return rightMaster.GetOutputCurrent();
}

double DriveBaseSubsystem::getLeftSMRate() {
	return leftEncoder.GetVelocity();
}

double DriveBaseSubsystem::getRightSMRate() {
	return leftEncoder.GetVelocity();
}