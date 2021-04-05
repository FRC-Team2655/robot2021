/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/BeltsSubsystem.h"

using NeutralMode = ctre::phoenix::motorcontrol::NeutralMode;

BeltsSubsystem::BeltsSubsystem() {
    #if COMPBOT
    bottomBelt.SetInverted(false);
    #else
    bottomBelt.SetInverted(true);
    #endif
    leftBelt.SetInverted(true);
}

void BeltsSubsystem::Periodic() {}

void BeltsSubsystem::runBelts(double speed, bool useProximitySensor) {
    if (useProximitySensor) {
        if (isProximSensorTopTriggered()) {
            runBeltsSpeeds(0, 0, 0);
            shouldRunBelts = false;
        }else if (isProximSensorMiddleTriggered() && !isProximSensorBottomTriggered()) {
            runBeltsSpeeds(beltsSpeed, bottomBeltSpeed, 0);
        }else if (isProximSensorMiddleTriggered() && isProximSensorBottomTriggered()) {
            runBeltsSpeeds(0, bottomBeltSpeed, kickerSpeed);
        }else{
            runBeltsSpeeds(beltsSpeed, bottomBeltSpeed, kickerSpeed);
        }
    }else{
        runBeltsSpeeds(beltsSpeed, bottomBeltSpeed, kickerSpeed);
    }
}

void BeltsSubsystem::stopBelts() {
    leftBelt.Set(0);
    rightBelt.Set(0);
    bottomBelt.Set(0);
    kicker.Set(0);
}

void BeltsSubsystem::setCoastMode() {
    kicker.SetNeutralMode(NeutralMode::Coast);
    leftBelt.SetNeutralMode(NeutralMode::Coast);
    rightBelt.SetNeutralMode(NeutralMode::Coast);
    bottomBelt.SetNeutralMode(NeutralMode::Coast);
}

bool BeltsSubsystem::isProximSensorTopTriggered() {
    return !proximSensorTop.Get();
}

bool BeltsSubsystem::isProximSensorMiddleTriggered() {
    return !proximSensorMiddle.Get();
}

bool BeltsSubsystem::isProximSensorBottomTriggered() {
    return !proximSensorBottom.Get();
}

void BeltsSubsystem::runBeltsSpeeds(double sidesSpeed, double bottomSpeed, double kickerSpeed) {
    static double firstSwitchTime = 0.0;
    static double secondSwitchTime = beltsSwitchTime;
    static double thirdSwitchTime = 2 * beltsSwitchTime;
    if(frc::Timer::GetFPGATimestamp() < firstSwitchTime)
    {
        leftBelt.Set(sidesSpeed);
        rightBelt.Set(-sidesSpeed);
    }
    else if(frc::Timer::GetFPGATimestamp() < secondSwitchTime)
    {
        leftBelt.Set(-sidesSpeed);
        rightBelt.Set(sidesSpeed);
    }
    else if(frc::Timer::GetFPGATimestamp() < thirdSwitchTime) {
        leftBelt.Set(sidesSpeed);
        rightBelt.Set(sidesSpeed);
    }
    else
    {
        firstSwitchTime = frc::Timer::GetFPGATimestamp() + beltsSwitchTime;
        secondSwitchTime = firstSwitchTime + beltsSwitchTime;
        thirdSwitchTime = secondSwitchTime + beltsSwitchTime;
    }
    bottomBelt.Set(bottomSpeed);
    kicker.Set(kickerSpeed);
}

void BeltsSubsystem::runBeltsInverted(double speed) {
    leftBelt.Set(-speed);
    rightBelt.Set(-speed);
    bottomBelt.Set(-speed);
    kicker.Set(-speed);
}

void BeltsSubsystem::runSideBelts() {
    rightBelt.Set(beltsSpeed);
    leftBelt.Set(beltsSpeed);
}

void BeltsSubsystem::runBottomBelt() {
    bottomBelt.Set(beltsSpeed);
}

void BeltsSubsystem::runKickerBelt() {
    kicker.Set(beltsSpeed);
}