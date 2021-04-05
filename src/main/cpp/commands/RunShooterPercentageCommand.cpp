#include "commands/RunShooterPercentageCommand.h"
#include "Robot.h"

RunShooterPercentageCommand::RunShooterPercentageCommand(double speed) : speed(speed){
}

void RunShooterPercentageCommand::Initialize() {
}

void RunShooterPercentageCommand::Execute() {
  Robot::shooter.runShooterPercentage(speed);
}

void RunShooterPercentageCommand::End(bool interrupted) {
  Robot::shooter.stopShooter();
}

bool RunShooterPercentageCommand::IsFinished() { return false; }
