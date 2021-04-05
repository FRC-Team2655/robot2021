#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

class RunShooterPercentageCommand
    : public frc2::CommandHelper<frc2::CommandBase, RunShooterPercentageCommand> {
 public:
  RunShooterPercentageCommand(double speed);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
private:
  double speed;
};
