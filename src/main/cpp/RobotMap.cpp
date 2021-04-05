/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotMap.h"

#if COMPBOT
const int LMaster = 1;
const int LSlave1 = 2;
const int LSlave2 = 3;

const int RMaster = 6;
const int RSlave1 = 5;
const int RSlave2 = 4;

const int Shooter1ID = 7;
const int Shooter2ID = 8;

const int IntakeArm = 11;

const int KickerID = 12;

const int BeltLeft = 15;
const int BeltRight = 14;
const int BeltBottom = 13;

const int RollerShooters = 16;

const int ClimbMotor1 = 9;
const int ClimbMotor2 = 10;
#else
const int LMaster = 1;
const int LSlave1 = 2;
const int LSlave2 = 3;

const int RMaster = 6;
const int RSlave1 = 5;
const int RSlave2 = 4;

const int Shooter1ID = 7;
const int Shooter2ID = 8;

const int IntakeArm = 9;

const int KickerID = 13;

const int BeltLeft = 10;
const int BeltRight = 11;
const int BeltBottom = 12;

const int RollerShooters = 14;
#endif


#if COMPBOT
const double MaxVelocity = 5500;    // This is capped at the slowest velocity on ANY robot to ensure that paths work the same
const double LMaxVelocity = 5400.0;
const double RMaxVelocity = 5800.0;
const double ShooterVelocity = 4900.0;

const double rollersSpeed = 0.55;
const double kickerSpeed = 0.35;
const double beltsSpeed = 0.7;
const double bottomBeltSpeed = 0.7;
#else
const double MaxVelocity = 5500;    // This is capped at the slowest velocity on ANY robot to ensure that paths work the same
const double LMaxVelocity = 5850.0;
const double RMaxVelocity = 5800.0;
const double ShooterVelocity = 5200.0;

const double rollersSpeed = 0.7;
const double kickerSpeed = 0.35;
const double beltsSpeed = 0.7;
const double bottomBeltSpeed = 0.7;
#endif

const double DriveRampRate = 0.23;  // Minimum time (sec) to go from 0 to full

#if COMPBOT
const int LEncA = 0;
const int LEncB = 1;
const int REncA = 2;
const int REncB = 3;
const int IntakePWM = 4;
const int LEDPWMPort = 9;

const int proximitySensorTopChannel = 7;
const int proximitySensorMiddleChannel = 8;
const int proximitySensorBottomChannel = 9;
#else
const int LEncA = 5;
const int LEncB = 0;
const int REncA = 1;
const int REncB = 2;
const int IntakePWM = 4;
const int LEDPWMPort = 9;

const int proximitySensorTopChannel = 7;
const int proximitySensorMiddleChannel = 9;
const int proximitySensorBottomChannel = 8;
#endif

const double incrementShooterSpeed = 0.05;
const double maxShooterSpeed = 0.9;

const double intakeInPosition = 0;
const double intakeOutPosition = -0.27;

const double armTolerance = 0.006;

const int GearRatio = 0.25;

const double armRestCurrent = 25;

const double beltsSwitchTime = 0.6;