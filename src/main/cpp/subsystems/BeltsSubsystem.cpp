/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/BeltsSubsystem.h"

using NeutralMode = ctre::phoenix::motorcontrol::NeutralMode;

BeltsSubsystem::BeltsSubsystem() {
    #if PRACTICEBOT
    bottomBelt.SetInverted(true);
    sideBelts.SetInverted(true);
    #endif
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

void BeltsSubsystem::runAllBelts(double speed) {
    #if PRACTICEBOT
    sideBelts.Set(speed);
    #else
    leftBelt.Set(speed);
    rightBelt.Set(speed);
    #endif

    bottomBelt.Set(speed);
    kicker.Set(speed);
}

void BeltsSubsystem::stopBelts() {
    #if PRACTICEBOT
    sideBelts.Set(0);
    #else
    leftBelt.Set(0);
    rightBelt.Set(0);
    #endif   
    bottomBelt.Set(0);
    kicker.Set(0);
}

void BeltsSubsystem::setCoastMode() {
    #if PRACTICEBOT
    sideBelts.SetNeutralMode(NeutralMode::Coast);
    #else
    leftBelt.SetNeutralMode(NeutralMode::Coast);
    rightBelt.SetNeutralMode(NeutralMode::Coast);
    #endif

    bottomBelt.SetNeutralMode(NeutralMode::Coast);
    kicker.SetNeutralMode(NeutralMode::Coast);
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

#if PRACTICEBOT
void BeltsSubsystem::runBeltsSpeeds(double sidesSpeed, double bottomSpeed, double kickerSpeed) {
    static double firstSwitchTime = 0.0;
    static double secondSwitchTime = beltsSwitchTime;
    //static double thirdSwitchTime = 2 * beltsSwitchTime;
    if(frc::Timer::GetFPGATimestamp() < firstSwitchTime)
    {
        /*elt.Set(sidesSpeed);
        rightBelt.Set(sidesSpeed); //-sidesSpeed);*/
        sideBelts.Set(-sidesSpeed);
    }
    else if(frc::Timer::GetFPGATimestamp() < secondSwitchTime)
    {
        //leftBelt.Set(sidesSpeed);//-sidesSpeed);
        //rightBelt.Set(sidesSpeed);
        sideBelts.Set(sidesSpeed);
    }else
    /*else if(frc::Timer::GetFPGATimestamp() < thirdSwitchTime) {
        leftBelt.Set(sidesSpeed);
        rightBelt.Set(sidesSpeed);
    }
    else*/
    {
        firstSwitchTime = frc::Timer::GetFPGATimestamp() + beltsSwitchTime;
        secondSwitchTime = firstSwitchTime + beltsSwitchTime;
        //thirdSwitchTime = secondSwitchTime + beltsSwitchTime;
    }
    bottomBelt.Set(bottomSpeed);
    kicker.Set(kickerSpeed);
}
#else
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
    }else if(frc::Timer::GetFPGATimestamp() < thirdSwitchTime) {
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
#endif

void BeltsSubsystem::runBeltsInverted(double speed) {
    #if PRACTICEBOT
    sideBelts.Set(-speed);
    #else
    leftBelt.Set(-speed);
    rightBelt.Set(-speed);
    #endif
    bottomBelt.Set(-speed);
    kicker.Set(-speed);
}

void BeltsSubsystem::runSideBelts() {
    #if PRACTICEBOT
    sideBelts.Set(beltsSpeed);
    #else
    rightBelt.Set(beltsSpeed);
    leftBelt.Set(beltsSpeed);
    #endif
}

void BeltsSubsystem::runBottomBelt() {
    bottomBelt.Set(beltsSpeed);
}

void BeltsSubsystem::runKickerBelt() {
    kicker.Set(beltsSpeed);
}