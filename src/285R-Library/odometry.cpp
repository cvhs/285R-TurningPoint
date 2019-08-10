#include "285R-Library/odometry.hpp"

AngleTracker::AngleTracker (double left, double right, double initialTheta)
{
  leftDist = left;
  rightDist = right;
  absTheta = initialTheta;

  std::valarray<std::int32_t> sensorVals = drive.getSensorVals();
}

void AngleTracker::track ()
{
  std::valarray<std::int32_t> sensorVals = drive.getSensorVals();

  deltaL = sensorVals[0] - lastL;
  deltaR = sensorVals[1] - lastR;

  absTheta += - (deltaL - deltaR) / (leftDist + rightDist);

  lastL = sensorVals[0];
  lastR = sensorVals[1];
}

double AngleTracker::getAngle (bool radians = true)
{
  if (radians)
    return absTheta;
  else
    return absTheta * 180/M_PI;
}
