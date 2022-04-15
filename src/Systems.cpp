#include "main.h"

Motor backLeft(backLeftPort, pros::E_MOTOR_GEARSET_18, backLeftReversed, pros::E_MOTOR_ENCODER_DEGREES);
Motor backRight(backRightPort, pros::E_MOTOR_GEARSET_18, backRightReversed, pros::E_MOTOR_ENCODER_DEGREES);
Motor frontLeft(frontLeftPort, pros::E_MOTOR_GEARSET_18, frontLeftReversed, pros::E_MOTOR_ENCODER_DEGREES);
Motor frontRight(frontRightPort, pros::E_MOTOR_GEARSET_18, frontRightReversed, pros::E_MOTOR_ENCODER_DEGREES);

Motor left4Bar(left4BarPort, pros::E_MOTOR_GEARSET_36, left4BarReversed, pros::E_MOTOR_ENCODER_DEGREES);
Motor right4Bar(right4BarPort, pros::E_MOTOR_GEARSET_36, right4BarReversed, pros::E_MOTOR_ENCODER_DEGREES);

Motor clamp(clampPort, pros::E_MOTOR_GEARSET_18, clampReversed, pros::E_MOTOR_ENCODER_DEGREES);

Motor lift(liftPort, pros::E_MOTOR_GEARSET_36, liftReversed, pros::E_MOTOR_ENCODER_DEGREES);

pros::Controller controller(pros::E_CONTROLLER_MASTER);

bool clampOn = false;