/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>
#include <frc2/command/RunCommand.h>
#include "commands/DriveDistanceCommand.h"
#include "commands/RotateDegreesCommand.h"
#include "commands/IntakeArmLockPIDCommand.h"
#include "commands/DelayMillisecondsCommand.h"
#include "commands/RunShooterVelocityCommand.h"
#include "commands/RunBeltsCommand.h"

#include <iostream>

DriveBaseSubsystem Robot::driveBase;
OI Robot::oi;
ShooterSubsystem Robot::shooter;
IntakeSubsystem Robot::intake;
BeltsSubsystem Robot::belts;
LEDSubsystem Robot::leds;
AutonomousRoutines Robot::autoRoutines;

void Robot::RobotInit() {
    autoChooser.SetDefaultOption("No Auto", -1);
    autoChooser.AddOption("Shoot Preloads Center", 0);
    autoChooser.AddOption("Shoot Preloads Center + Trench Pickup", 3);
    autoChooser.AddOption("Test Auto Routine", 1);
    autoChooser.AddOption("5 Ball Auto", 2);


    /* Apply auto chooser to smart dash*/
    frc::SmartDashboard::PutData("Choose Auto: ", &autoChooser);

    /* Auto options */
    frc::SmartDashboard::PutNumber("Auto Distance: ", autoDistance);
    frc::SmartDashboard::PutNumber("Encoder Auto P: ", penc);
    frc::SmartDashboard::PutNumber("Gyro Auto P: ", pgyro);
    frc::SmartDashboard::PutNumber("Rotate Gyro P: ", rotatePGyro);
    frc::SmartDashboard::PutNumber("Auto Degrees: ", autoDegrees);
    frc::SmartDashboard::PutNumber("Auto Start Delay(ms): ", autoStartDelayMs);
    frc::SmartDashboard::PutNumber("Preload Auto Offset (inches): ", preloadStartOffset);

    frc::SmartDashboard::PutBoolean("Reset Encoders", false);

    frc::SmartDashboard::PutNumber("Intake In P: ", kInP);
    frc::SmartDashboard::PutNumber("Intake In I: ", kInI);
    frc::SmartDashboard::PutNumber("Intake In D: ", kInD);
    frc::SmartDashboard::PutNumber("Intake Out P: ", kOutP);
    frc::SmartDashboard::PutNumber("Intake Out I: ", kOutI);
    frc::SmartDashboard::PutNumber("Intake Out D: ", kOutD);
    frc::SmartDashboard::PutNumber("Intake Lock P: ", kLockP);
    frc::SmartDashboard::PutNumber("Intake Lock I: ", kLockI);
    frc::SmartDashboard::PutNumber("Intake Lock D: ", kLockD);
    frc::SmartDashboard::PutNumber("Left P: ", driveBase.kPLeft);
    frc::SmartDashboard::PutNumber("Right P: ", driveBase.kPRight);
    frc::SmartDashboard::PutNumber("Left I: ", driveBase.kILeft);
    frc::SmartDashboard::PutNumber("Right I: ", driveBase.kIRight);
    frc::SmartDashboard::PutNumber("Shooter P: ", shooter.kP);
    frc::SmartDashboard::PutNumber("Shooter I: ", shooter.kI);
    frc::SmartDashboard::PutNumber("Shooter D: ", shooter.kD);
    frc::SmartDashboard::PutNumber("Shooter FF: ", shooter.kFF);
    frc::SmartDashboard::PutNumber("Simple Auto Buddy: ", buddyDrive);

    shooter.setCoastMode();
    belts.setCoastMode();
    driveBase.setCoastMode();
    intake.setArmBrakeMode();
    intake.setRollersCoastMode();
    intake.setRollersCoastMode();
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() { 

    frc::SmartDashboard::PutNumber("Left Current: ", driveBase.leftCurrent());
    frc::SmartDashboard::PutNumber("Right Current: ", driveBase.rightCurrent());

    frc::SmartDashboard::PutNumber("Left Rotations: ", driveBase.getLeftEncoderRotations());
    frc::SmartDashboard::PutNumber("Right Rotations: ", driveBase.getRightEncoderRotations());
    frc::SmartDashboard::PutNumber("Left Rate: ", driveBase.getLeftEncoderRate());
    frc::SmartDashboard::PutNumber("Right Rate: ", driveBase.getRightEncoderRate());
    frc::SmartDashboard::PutNumber("Right SM Rate: ", driveBase.getRightSMRate());
    frc::SmartDashboard::PutNumber("Left SM Rate: ", driveBase.getLeftSMRate());

    frc::SmartDashboard::PutNumber("Shooter Current: ", shooter.getAvgCurrent());

    frc::SmartDashboard::PutNumber("Top Sensor: ", belts.isProximSensorTopTriggered());
    frc::SmartDashboard::PutNumber("Middle Sensor: ", belts.isProximSensorMiddleTriggered());
    frc::SmartDashboard::PutNumber("Bottom Sensor: ", belts.isProximSensorBottomTriggered());

    frc::SmartDashboard::PutNumber("Gyro Angle: ", driveBase.getIMUAngle());
    frc::SmartDashboard::PutNumber("Intake Arm Current: ", intake.intakeArmCurrent());
    frc::SmartDashboard::PutNumber("Intake Arm Position: ", intake.armPosition());
    frc::SmartDashboard::PutNumber("Intake Arm Percentage: ", intake.intakeMotorValue);
    frc::SmartDashboard::PutNumber("Shooter Rate: ", shooter.getRPM());

    if (frc::SmartDashboard::GetBoolean("Reset Encoders", false) == true) {
        driveBase.resetEncoders();
        frc::SmartDashboard::PutBoolean("Reset Encoders", false);
    }
    if (frc::SmartDashboard::GetNumber("Intake In P: ", 0) != kInP) {
        kInP = frc::SmartDashboard::GetNumber("Intake In P: ", 0);
        intake.intakeInPID.SetP(kInP);
    }
    if (frc::SmartDashboard::GetNumber("Intake In I: ", 0) != kInI) {
        kInI = frc::SmartDashboard::GetNumber("Intake In I: ", 0);
        intake.intakeInPID.SetI(kInI);
    }
    if (frc::SmartDashboard::GetNumber("Intake In D: ", 0) != kInD) {
        kInD = frc::SmartDashboard::GetNumber("Intake In D: ", 0);
        intake.intakeInPID.SetD(kInD);
    }
    if (frc::SmartDashboard::GetNumber("Intake Out D: ", 0) != kOutD) {
        kOutD = frc::SmartDashboard::GetNumber("Intake Out D: ", 0);
        intake.intakeOutPID.SetD(kOutD);
    }
    if (frc::SmartDashboard::GetNumber("Intake Out P: ", 0) != kOutP) {
        kOutP = frc::SmartDashboard::GetNumber("Intake Out P: ", 0);
        intake.intakeOutPID.SetP(kOutP);
    }
    if (frc::SmartDashboard::GetNumber("Intake Out I: ", 0) != kOutI) {
        kOutI = frc::SmartDashboard::GetNumber("Intake Out I: ", 0);
        intake.intakeOutPID.SetI(kOutI);
    }
    if (frc::SmartDashboard::GetNumber("Intake Velocity: ", 0) != intake.kVelocity_) {
        intake.kVelocity_ = frc::SmartDashboard::GetNumber("Intake Velocity: ", intake.kVelocity_);
    }
    if (frc::SmartDashboard::GetNumber("Intake Lock P: ", 0) != kLockP) {
        kLockP = frc::SmartDashboard::GetNumber("Intake Lock P: ", 0);
        intake.intakeLockPID.SetP(kLockP);
    }
    if (frc::SmartDashboard::GetNumber("Intake Lock I: ", 0) != kLockI) {
        kLockI = frc::SmartDashboard::GetNumber("Intake Lock I: ", 0);
        intake.intakeLockPID.SetI(kLockI);
    }
    if (frc::SmartDashboard::GetNumber("Intake Lock D: ", 0) != kLockD) {
        kLockD = frc::SmartDashboard::GetNumber("Intake Lock D: ", 0);
        intake.intakeLockPID.SetD(kLockD);
    }
    if (frc::SmartDashboard::GetNumber("Left P: ", 0) != driveBase.kPLeft) {
        driveBase.kPLeft = frc::SmartDashboard::GetNumber("Left P: ", 0);
        driveBase.leftPID.SetP(driveBase.kPLeft);
    }
    if (frc::SmartDashboard::GetNumber("Right P: ", 0) != driveBase.kPRight) {
        driveBase.kPRight = frc::SmartDashboard::GetNumber("Right P: ", 0);
        driveBase.rightPID.SetP(driveBase.kPRight);
    }
    if (frc::SmartDashboard::GetNumber("Left I: ", 0) != driveBase.kILeft) {
        driveBase.kILeft = frc::SmartDashboard::GetNumber("Left I: ", 0);
        driveBase.leftPID.SetI(driveBase.kILeft);
    }
    if (frc::SmartDashboard::GetNumber("Right I: ", 0) != driveBase.kIRight) {
        driveBase.kIRight = frc::SmartDashboard::GetNumber("Right I: ", 0);
        driveBase.rightPID.SetI(driveBase.kIRight);
    }
    if (frc::SmartDashboard::GetNumber("Shooter P: ", 0) != shooter.kP) {
        shooter.kP = frc::SmartDashboard::GetNumber("Shooter P: ", 0);
    }
    if (frc::SmartDashboard::GetNumber("Shooter I: ", 0) != shooter.kI) {
        shooter.kI = frc::SmartDashboard::GetNumber("Shooter I: ", 0);
    }
    if (frc::SmartDashboard::GetNumber("Shooter D: ", 0) != shooter.kD) {
        shooter.kD = frc::SmartDashboard::GetNumber("Shooter D: ", 0);
    }
    if (frc::SmartDashboard::GetNumber("Shooter FF: ", 0) != shooter.kFF) {
        shooter.kFF = frc::SmartDashboard::GetNumber("Shooter FF: ", 0);
    }

    /* Get auto values */
    autoStartDelayMs = frc::SmartDashboard::GetNumber("Auto Start Delay(ms): ", 0);
    autoDistance = frc::SmartDashboard::GetNumber("Auto Distance: ", 0);
    penc = frc::SmartDashboard::GetNumber("Encoder Auto P: ", 0);
    pgyro = frc::SmartDashboard::GetNumber("Gyro Auto P: ", 0);
    autoDegrees = frc::SmartDashboard::GetNumber("Auto Degrees: ", 0);
    preloadStartOffset = frc::SmartDashboard::GetNumber("Preload Auto Offset (inches): ", 0);
    rotatePGyro = frc::SmartDashboard::GetNumber("Rotate Gyro P: ", 0);
    frc::SmartDashboard::PutData("Choose Auto: ", &autoChooser);
    buddyDrive = frc::SmartDashboard::GetNumber("Simple Auto Buddy: ", 0);

    frc2::CommandScheduler::GetInstance().Run();
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {
    driveBase.setBrakeMode();
    intake.isIntakeLocked = false;
}

void Robot::DisabledPeriodic() {
    leds.setLEDColor(LEDSubsystem::LEDColors::BlueViolet);
}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit() {

    /* Put drive base in brake mode for auto*/
    driveBase.setBrakeMode();
    /* Zero the intake encoder */
    intake.updateOffset();
    /* Start applying lock PID */
    intake.isIntakeLocked = true;

    /* Clear gyro angle accumulator */
    driveBase.resetIMUAngle();

    /* Apply feedback terms to auto routines */
    autoRoutines.driveDistance_P_encoder = penc;
    autoRoutines.driveDistance_P_gyro = pgyro;
    autoRoutines.rotate_P_gyro = rotatePGyro;

    /* Get selected index */
    int index = autoChooser.GetSelected();

    /* Choose auto routine based on the index */
    switch(index) {
        case -1:
            autonomousCommand = nullptr;
            break;
        case 0:
            if (buddyDrive == 0) {
                autonomousCommand = autoRoutines.ShootPreloads(0, 0, false, false, 0);
            }else{
                autonomousCommand = autoRoutines.ShootPreloads(0, 0, true, false, 0);
            }
            break;
        case 1:
            autonomousCommand = autoRoutines.TestAuto(autoDistance, autoDegrees);
            break;
        case 2:
            autonomousCommand = autoRoutines.PickupFromTrechAndShoot(driveBase.getIMUAngle());
            break;
        case 3:
            /*Shoot preloads + pickup from trench */
            if (buddyDrive == 0) {
                autonomousCommand = autoRoutines.ShootPreloads(0, 0, false, true, driveBase.getIMUAngle());
            }else{
                autonomousCommand = autoRoutines.ShootPreloads(0, 0, true, true, driveBase.getIMUAngle());
            }
            break;
        default:
            autonomousCommand = nullptr;
            break;
    }

    /* schedule the command */
    if(autonomousCommand != nullptr)
        autonomousCommand->Schedule();
}

void Robot::AutonomousPeriodic() {
    if (intake.isIntakeLocked) {
        intake.setLockPID();
        std::cout << "Locked in" << std::endl;
    }else if (intake.isIntakeOut) {
        intake.setLockDownPID();
        std::cout << "Locked out" << std::endl;
    }
}

void Robot::TeleopInit() {
    if (autonomousCommand != nullptr) {
        autonomousCommand->Cancel();
        autonomousCommand = nullptr;
    }

    driveBase.setCoastMode();
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() {
    //driveBase.rightMaster.Set(1);
    //driveBase.rightSlave1.Set(1);
    //driveBase.leftSlave2.Set(1);

    if (intake.isIntakeLocked) {
        intake.setLockPID();
        std::cout << "Locked in" << std::endl;
    }else if (intake.isIntakeOut) {
        intake.setLockDownPID();
        std::cout << "Locked out" << std::endl;
    }


    ////////LED Control//////////////

    // Shooter not running
    if (!shooter.isShooterRunning) {
        // Intake in
        if (!intake.isIntakeOut) {
            leds.setLEDColor(LEDSubsystem::LEDColors::Black);
        // Intake out
        }else{
            leds.setLEDColor(LEDSubsystem::LEDColors::Red);
        }

    // Shooter ramping up
    }else if (!shooter.isShooterAtMax && shooter.isShooterRunning) {
        // Intake in
        if (!intake.isIntakeOut) {
            leds.setLEDColor(LEDSubsystem::LEDColors::Yellow);
        // Intake out
        }else{
            leds.setDualColorMode();
        }

    // Shooter at max speed
    }else if (shooter.isShooterAtMax) {
        // Intake in
        if (!intake.isIntakeOut) {
            leds.setLEDColor(LEDSubsystem::LEDColors::Green);
        // Intake out
        }else{
            leds.setLEDColor(LEDSubsystem::LEDColors::Blue);
        }
    }

    std::cout << "Intake out: " << intake.isIntakeOut << std::endl;
}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif