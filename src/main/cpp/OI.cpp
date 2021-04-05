#include "OI.h"
#include "Robot.h"

using namespace team2655;

OI::OI() {
  js0 = new frc::Joystick(0);
  //js1 = new frc::Joystick(1);
  
  runButtons();
}

void OI::runButtons() {
  xBtn = new frc2::JoystickButton(js0, 2);
  squareBtn = new frc2::JoystickButton(js0, 1);
  triangleBtn = new frc2::JoystickButton(js0, 4);
  circleBtn = new frc2::JoystickButton(js0, 3);
  l2Btn = new frc2::JoystickButton(js0, 7);
  r2Btn = new frc2::JoystickButton(js0, 8);
  r1Btn = new frc2::JoystickButton(js0, 6);
  shareBtn = new frc2::JoystickButton(js0, 9);
  optionsBtn = new frc2::JoystickButton(js0, 10);

  //shareBtn1 = new frc2::JoystickButton(js1, 9);
  //r1Btn1 = new frc2::JoystickButton(js1, 6);
  //r2Btn1 = new frc2::JoystickButton(js1, 8);
  //l2Btn1 = new frc2::JoystickButton(js1, 7);
  //l1Btn1 = new frc2::JoystickButton(js1, 5);
  //triangleBtn1 = new frc2::JoystickButton(js1, 4);
  //xBtn1 = new frc2::JoystickButton(js1, 2);

  l2Btn->WhileHeld(rsVelocityCommand);
  r2Btn->WhileHeld(rbCommand, false);
  triangleBtn->WhileHeld(invertrbCommand);
  shareBtn->WhenPressed(updateIntakeOffsetUp);
  optionsBtn->WhenPressed(updateIntakeOffsetDown);
  r1Btn->WhileHeld(riRollersCommand);
  circleBtn->WhenPressed(frc2::SequentialCommandGroup(MoveIntakeOutArmCommand(-0.26), RunBeltsBackgroundCommand(0.5)), true);
  squareBtn->WhenPressed(frc2::SequentialCommandGroup(MoveIntakeInArmCommand(0), IntakeArmLockPIDCommand()), true);

  //r2Btn1->WhileHeld(rsVelocityCommand);
  //l1Btn1->WhileHeld(riRollersInvertCommand);
  //r1Btn1->WhileHeld(riRollersCommand);
  //shareBtn1->WhileHeld(invertrbCommand);
  //triangleBtn1->WhenPressed(updateIntakeOffsetUp);
  //xBtn1->WhenPressed(updateIntakeOffsetDown);
  //l2Btn1->WhileHeld(rbCommand);
}