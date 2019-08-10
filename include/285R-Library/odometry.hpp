#define _USE_MATH_DEFINES

#include "main.h"
#include "285R-Main/initRobot.hpp"
#include <valarray>
#include <cmath>

// std::valarray<std::int32_t> sensorValsBeta = drive.getSensorVals();

class AngleTracker
{
  private:
    double absTheta  {0};
    double leftDist  {0};
    double rightDist {0};

    double deltaL {0};
    double deltaR {0};

    double lastL {0};
    double lastR {0};

  public:
    AngleTracker (double left, double right, double initialTheta);

    void track ();

    double getAngle (bool radians);
};
