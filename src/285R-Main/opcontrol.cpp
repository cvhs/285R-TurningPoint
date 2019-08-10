#include "285R-Library/GUI.hpp"
#include "285R-Main/initRobot.hpp"
#include "285R-Library/odometry.hpp"

void opcontrol()
{
  AngleTracker testTracker {6.625, 6.625, 0};

  l.tarePosition();
  while(ONLINE)
  {
    testTracker.track();
    gui285R::brainPower(testTracker.getAngle(false));

    flywheel.moveVelocity(190);

    if (btnLazyMode.changedToPressed())
      lazy = !lazy;

    driveStyle();

    doubleShotControl();
    ballControl();
    lControl();
  }
}
