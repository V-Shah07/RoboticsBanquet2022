#include "main.h"

const int backLeftPort = 1;
const int backRightPort = 2;
const int frontLeftPort = 3;
const int frontRightPort = 4;
const bool backLeftReversed = false;
const bool backRightReversed = false;
const bool frontLeftReversed = false;
const bool frontRightReversed = false;

const int left4BarPort = 5;
const int right4BarPort = 6;
const bool left4BarReversed = false;
const bool right4BarReversed = false;

const int clampPort = 7;
const bool clampReversed = false;

const int liftPort = 8;
const bool liftReversed = false;

//Drive motors
extern Motor backLeft;
extern Motor backRight;
extern Motor frontLeft;
extern Motor frontRight;

//4 bar motors
extern Motor left4Bar;
extern Motor right4Bar;

//clamp motor
extern Motor clamp;

//lift motor
extern Motor lift;

pros::Controller controller;

extern bool clampOn;