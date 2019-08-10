#include "285R-Main/initRobot.hpp"

Controller joystick;

ControllerButton btnShoot												(ControllerDigital::R2);
ControllerButton btnBallIntake									(ControllerDigital::R1);
ControllerButton btnReverseBallSystem						(ControllerDigital::L1);
ControllerButton btnDoubleShot                  (ControllerDigital::X );

ControllerButton btnLUsager                     (ControllerDigital::L2);         //> 'L' refers to the robot's arm which was in the shape of an 'L' in its ealy days

ControllerButton btnLazyMode										(ControllerDigital::up);
ControllerButton btnDriveStyle                  (ControllerDigital::down);
ControllerButton btnIntakeStyle                 (ControllerDigital::left);

bool intakeStyleToggle  {TOGGLE};
bool ballIntakeToggle   {false};
bool driveStyleToggle   {ARCADE};
bool doubleShot         {false};
bool lUsage             {false};
bool lazy               {false};

void lControl ()
{
  if (btnLUsager.changedToPressed())
    lUsage = !lUsage;

  if (lUsage)
  {
    l.moveAbsolute(-280, 200);
  }
  else
  {
    l.moveAbsolute(0, 200);
  }
}

void intakeStyle ()
{
  if (btnIntakeStyle.changedToPressed())
  {
    intakeStyleToggle = !intakeStyleToggle;
  }

  if (intakeStyleToggle)
  {
    if (btnShoot.isPressed())
    {
      ballIndexer.moveVelocity  (200);
      ballIntake.moveVelocity   (420);
      if (doubleShot)
        doubleShotControl();
    }
    else if (btnReverseBallSystem.isPressed())
    {
      ballIndexer.moveVelocity  (-200);
      ballIntake.moveVelocity   (-420);
    }
    else if(ballIntakeToggle)
    {
      ballIntake.moveVelocity   (200);
      ballIndexer.moveVelocity  (0);
    }
    else
    {
      ballIndexer.moveVelocity	(0);
      ballIntake.moveVelocity	  (0);
    }
  }
  else
  {
    if (btnShoot.isPressed())
    {
      ballIndexer.moveVelocity(200);
      ballIntake.moveVelocity (420);
      if (doubleShot)
        doubleShotControl();
    }
    else if (btnReverseBallSystem.isPressed())
    {
      ballIndexer.moveVelocity(-200);
      ballIntake.moveVelocity (-420);
    }
    else if(btnBallIntake.isPressed())
    {
      ballIndexer.moveVelocity(0);
      ballIntake.moveVelocity (420);
    }
    else
    {
      ballIndexer.moveVelocity(0);
      ballIntake.moveVelocity	(0);
    }
  }
}

void ballControl ()
{
  if (btnBallIntake.changedToPressed())
    ballIntakeToggle = !ballIntakeToggle;

  if (btnDoubleShot.changedToPressed())
  {
    doubleShot = true;
    joystick.setText(0, 0, "Double Shot On");
  }

  intakeStyle();
}

void doubleShotControl ()
{
  if (flywheel.getTargetVelocity() - flywheel.getActualVelocity() > 15 && doubleShot)
  {
    doubleShot = false;

    ballIntake.moveVelocity(0);
    ballIndexer.moveVelocity(0);

    flywheel.moveVelocity(140);
    while (flywheel.getActualVelocity() <= 138)
      pros::Task::delay(10);

    ballIntake.moveVelocity(420);
    ballIndexer.moveVelocity(200);

    pros::Task::delay(500);

    joystick.clearLine(0);
  }
}

void lazyMode ()
{
  drive.stop();

  driveL.tarePosition();
  driveR.tarePosition();

  driveL.setBrakeMode(AbstractMotor::brakeMode::hold);
  driveR.setBrakeMode(AbstractMotor::brakeMode::hold);

  pros::Task::delay(500);

  driveL.moveAbsolute(0, 200);
  driveR.moveAbsolute(0, 200);
}

void doArcade ()
{
  if (!lazy)
  {
    driveL.setBrakeMode(AbstractMotor::brakeMode::brake);
    driveR.setBrakeMode(AbstractMotor::brakeMode::brake);
    drive.arcade
    (
      joystick.getAnalog(ControllerAnalog::leftY),
      joystick.getAnalog(ControllerAnalog::rightX)
    );
  }
  else
    lazyMode();
}

void doTank ()
{
  if (!lazy)
  {
    driveL.setBrakeMode(AbstractMotor::brakeMode::brake);
    driveR.setBrakeMode(AbstractMotor::brakeMode::brake);
    drive.tank
    (
      joystick.getAnalog(ControllerAnalog::leftY),
      joystick.getAnalog(ControllerAnalog::rightY)
    );
  }
  else
    lazyMode();
}

void driveStyle ()
{
  if (btnDriveStyle.changedToPressed())
  {
    driveStyleToggle = !driveStyleToggle;
  }

  if (driveStyleToggle)
    doArcade();
  else
    doTank();
}
