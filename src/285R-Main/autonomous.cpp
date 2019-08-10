#include "285R-Main/initRobot.hpp"
#include "285R-Library/waypoints.hpp"

void autonomous()
{
  profile.generatePath({initRed, redBall}, "Ball");
  profile.setTarget("Ball", FWD);
  profile.waitUntilSettled();

  profile.generatePath({initRed, redBall}, "Ball");
  profile.setTarget("Ball", BWD);
  profile.waitUntilSettled();
}
