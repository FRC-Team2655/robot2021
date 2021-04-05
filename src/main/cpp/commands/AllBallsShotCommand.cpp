/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AllBallsShotCommand.h"
#include "frc/Timer.h"
#include "Robot.h"

AllBallsShotCommand::AllBallsShotCommand(double minTimeMs, double maxTimeMs): minTimeMs(minTimeMs), maxTimeMs(maxTimeMs) {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void AllBallsShotCommand::Initialize() {
  /* Get the start time */
  startTime = frc::Timer::GetFPGATimestamp();
  currentTime = startTime;
  /* Find end times */
  minEndTime = startTime + (minTimeMs / 1000.0);
  maxEndTime = startTime + (maxTimeMs / 1000.0);
  
  lastSensorTriggerTime = currentTime;
}

// Called repeatedly when this Command is scheduled to run
void AllBallsShotCommand::Execute() {
  /* Update time */
  currentTime = frc::Timer::GetFPGATimestamp();

  /* Get proxim sensor values */
  lowSensor = Robot::belts.isProximSensorBottomTriggered();
  midSensor = Robot::belts.isProximSensorMiddleTriggered();
  upperSensor = Robot::belts.isProximSensorTopTriggered();

  if (lowSensor || midSensor || upperSensor)
  {
    lastSensorTriggerTime = currentTime; 
  }
}

// Called once the command ends or is interrupted.
void AllBallsShotCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool AllBallsShotCommand::IsFinished() {
  /* Min time must have elapsed */
  if(currentTime < minEndTime)
    return false;
  
  /* Finish if max time has elapsed */
  if(currentTime >= maxEndTime)
    return true;

  if((currentTime - lastSensorTriggerTime) > 0.75)
    return true;
  
  return false;
}
