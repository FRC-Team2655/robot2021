/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/IntakeSubsystem.h"
#include "Robot.h"

using NeutralMode = ctre::phoenix::motorcontrol::NeutralMode;
using IdleMode = rev::CANSparkMax::IdleMode;

IntakeSubsystem::IntakeSubsystem() {
    isIntakeLocked = true;
    isIntakeOut = false;

    intakeArm.SetSmartCurrentLimit(armRestCurrent);

    #if PRACTICEBOT
    intakeRollers.SetInverted(true);
    #else
    intakeRollers.SetInverted(false);
    #endif

    intakeArm.BurnFlash();
}

// This method will be called once per scheduler run
void IntakeSubsystem::Periodic() {}

void IntakeSubsystem::runRollers(double speed) {
    intakeRollers.Set(speed);
}

void IntakeSubsystem::stopRollers() {
    intakeRollers.Set(0);
}

void IntakeSubsystem::moveArmIn() {
    intakeMotorValue = intakeInPID.Calculate(armPosition());

    intakeArm.Set(intakeMotorValue);
}

void IntakeSubsystem::moveArmOut() {
    intakeMotorValue = intakeOutPID.Calculate(armPosition());

    intakeArm.Set(intakeMotorValue);
}

double IntakeSubsystem::armRawPosition() {
    static double lastArmVal = 0;
    double read0, read1;
    int count = 0;
    read0 = 0;
    read1 = 1;
    while(count < 10 && read0 != read1)
    {
        read0 = intakeEnc.GetOutput();
        count++;
        read1 = intakeEnc.GetOutput();
    }
    if(count < 10)
    {
        //update arm value if they were equal
        lastArmVal = read0;
    }

    //invert output
    return -1 * lastArmVal;
} 

double IntakeSubsystem::armPosition() {
    return (double)(intakePositionOffset - armRawPosition());
}

void IntakeSubsystem::setRollersCoastMode() {
    intakeRollers.SetNeutralMode(NeutralMode::Coast);
}

void IntakeSubsystem::setArmBrakeMode() {
    intakeArm.SetIdleMode(IdleMode::kBrake);
}

void IntakeSubsystem::setArmCoastMode() {
    intakeArm.SetIdleMode(IdleMode::kCoast);
}

double IntakeSubsystem::intakeArmCurrent() {
    return intakeArm.GetOutputCurrent();
}

void IntakeSubsystem::stopArm() {
    intakeArm.Set(0);
}

void IntakeSubsystem::updateOffset() {
    intakePositionOffset = armRawPosition();
    std::cout << intakePositionOffset << std::endl;
}

void IntakeSubsystem::updateOffsetDown() {
    intakePositionOffset = (armRawPosition() - 0.29);
    std::cout << intakePositionOffset << std::endl;
}

void IntakeSubsystem::setCurrent(double current) {
    intakeArm.SetSmartCurrentLimit(current);
}

void IntakeSubsystem::setCurrent40() {
    intakeArm.SetSmartCurrentLimit(40);
}

void IntakeSubsystem::setLockPID() {
    setCurrent40();

    intakeLockPID.SetSetpoint(intakeInPosition);
    intakeLockPID.SetTolerance(0.000001);
    intakeMotorValue = intakeLockPID.Calculate(armPosition());
    intakeArm.Set(intakeMotorValue);
}

void IntakeSubsystem::setLockDownPID() {
    setCurrent40();

    intakeLockDownPID.SetSetpoint(intakeOutPosition);
    intakeLockDownPID.SetTolerance(0.0);
    intakeMotorValue = intakeLockDownPID.Calculate(armPosition());
    intakeArm.Set(intakeMotorValue);
}

void IntakeSubsystem::setInPID() {
    intakeLockPID.SetSetpoint(intakeInPosition);

    intakeMotorValue = intakeInPID.Calculate(armPosition());

    intakeArm.Set(intakeMotorValue);
}

void IntakeSubsystem::moveArmManual() {
    intakeArm.Set(0.2);
}

void IntakeSubsystem::resetArmEnc() {
    //intakeEnc.Reset();
}