#pragma once

#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/button/Button.h>

#include "RobotMap.h"
#include "team2655/joystick.hpp"

#include "commands/RunShooterPercentageCommand.h"
#include "commands/RunShooterVelocityCommand.h"
#include "subsystems/ShooterSubsystem.h"
#include "commands/RunBeltsCommand.h"
#include "commands/RunIntakeRollersCommand.h"
#include "commands/MoveIntakeInArmCommand.h"
#include "commands/MoveIntakeOutArmCommand.h"
#include "commands/RunBeltsBackgroundCommand.h"
#include <frc2/command/SequentialCommandGroup.h>
#include "commands/RunBeltsInvertedCommand.h"
#include "commands/MoveArmManualCommand.h"
#include "commands/IntakeArmLockPIDCommand.h"
#include "commands/UpdateIntakeOffsetDownCommand.h"
#include "commands/UpdateIntakeOffsetUpCommand.h"

#include "commands/RunBottomBeltCommand.h"
#include "commands/RunKickerBeltCommand.h"
#include "commands/RunSideBeltsCommand.h"

#include <frc/Joystick.h>

using namespace team2655;

class OI {
public:
  OI();
  frc::Joystick *js0;
  //frc::Joystick *js1;
  frc2::JoystickButton *xBtn;
  frc2::JoystickButton *xBtn1;
  frc2::JoystickButton *squareBtn;  
  frc2::JoystickButton *triangleBtn;
  frc2::JoystickButton *triangleBtn1;
  frc2::JoystickButton *circleBtn;
  frc2::JoystickButton *l2Btn;
  frc2::JoystickButton *l2Btn1;
  frc2::JoystickButton *l1Btn1;
  frc2::JoystickButton *r2Btn;
  frc2::JoystickButton *r2Btn1;
  frc2::JoystickButton *r1Btn;
  frc2::JoystickButton *r1Btn1;
  frc2::JoystickButton *shareBtn;
  frc2::JoystickButton *shareBtn1;
  frc2::JoystickButton *optionsBtn;
 
  RunShooterVelocityCommand rsVelocityCommand {};
  RunBeltsCommand rbCommand {beltsSpeed};
  RunBeltsInvertedCommand invertrbCommand {0.8 * beltsSpeed};
  RunIntakeRollersCommand riRollersCommand {rollersSpeed};
  RunIntakeRollersCommand riRollersInvertCommand {-rollersSpeed};
  MoveIntakeInArmCommand miInCommand {intakeInPosition};
  MoveIntakeOutArmCommand  miOutCommand {intakeOutPosition};
  MoveArmManualCommand maManCommand {};

  RunKickerBeltCommand rkBeltCommand {};
  RunSideBeltsCommand rsBeltsCommand {};
  RunBottomBeltCommand rbBeltsCommand {};

  UpdateIntakeOffsetUpCommand updateIntakeOffsetUp {};
  UpdateIntakeOffsetDownCommand updateIntakeOffsetDown {};

  // Configurations for the joystick deadband and cubic function.
  jshelper::AxisConfig driveAxisConfig = jshelper::createAxisConfig(.1, 0, 0.5);
  jshelper::AxisConfig rotateAxisConfig = jshelper::createAxisConfig(0.1);
  
  void runButtons();
};