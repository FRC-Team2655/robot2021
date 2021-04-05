/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DelayMillisecondsCommand.h"

DelayMillisecondsCommand::DelayMillisecondsCommand(double time_ms) : time_ms(time_ms) {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void DelayMillisecondsCommand::Initialize() {
  /* Get FPGA timestamp */
  currentTime = frc::Timer::GetFPGATimestamp();
  stopTime = currentTime + (time_ms / 1000.0);
}

// Called repeatedly when this Command is scheduled to run
void DelayMillisecondsCommand::Execute() {
  /* Update the current time */
  currentTime = frc::Timer::GetFPGATimestamp();
}

// Called once the command ends or is interrupted.
void DelayMillisecondsCommand::End(bool interrupted) {
  if (currentTime >= stopTime)
    std::cout << "Exited DelayMillisecondsCommand due to timeout" << std::endl;
}

// Returns true when the command should end.
bool DelayMillisecondsCommand::IsFinished() {
  return currentTime >= stopTime;
}
