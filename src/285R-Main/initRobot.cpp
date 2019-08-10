#include "285R-Main/initRobot.hpp"

Motor ballIntake  (4, true,  AbstractMotor::gearset::blue );
Motor ballIndexer (5, false, AbstractMotor::gearset::green);
Motor flywheel    (6, false, AbstractMotor::gearset::green);
Motor l           (7, true,  AbstractMotor::gearset::green);

ChassisControllerIntegrated drive = ChassisControllerFactory::create
(
   {1, -2},
   {-10, 9},
   AbstractMotor::gearset::green,
   {4.125_in, 11.375_in}
);

MotorGroup driveL = MotorGroup({1, -2});
MotorGroup driveR = MotorGroup({9, -10});
