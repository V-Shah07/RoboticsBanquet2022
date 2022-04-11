#include "main.h"

const double powerMultiplier = 1.5;
const double leftMultiplier = 1.0;
const double rightMultiplier = 1.0;
const double fourBarMultiplier = 1.5;
const int mogoLiftVelocity = 100;
const int clampVelocity = 100;
const int fourBarVelocity = 100;
void moveDrive()
{
    double power = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    double turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);

    power *= powerMultiplier;

    if(abs(power) <= 20)
    {
        power = 0;
    }
    if(abs(turn) <= 20)
    {
        turn = 0;
    }
    int leftVelocity = power + (turn * leftMultiplier); 
    int rightVelocity = power - (turn * rightMultiplier); 

    frontLeft.move_velocity(leftVelocity);
    backLeft.move_velocity(leftVelocity);
    frontRight.move_velocity(rightVelocity);
    backRight.move_velocity(rightVelocity);

}
void moveLift()
{
    bool up = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
    bool down = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
    if(up)
    {
        lift.move_velocity(mogoLiftVelocity);
    }
    else if(down)
    {
        lift.move_velocity(-mogoLiftVelocity);
    }
    else
    {
        lift.move_velocity(0);

    }
}
void moveClamp()
{
    bool grip = controller.get_digital(pros::E_CONTROLLER_DIGITAL_A);
    bool release = controller.get_digital(pros::E_CONTROLLER_DIGITAL_B);
    if(grip)
    {
        clampOn = true;
    }
    else if (release)
    {
        clampOn = false;
        clamp.tare_position();
        while(clamp.get_position() > -500)
        {
            clamp.move_velocity(-clampVelocity);
        }
    }
    if(clampOn)
    {
        clamp.move_velocity(clampVelocity);
    }
    else
    {
        clamp.move_velocity(0);
    }
}
void move4Bar()
{
    double verticalMovement = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    if(abs(verticalMovement) < 20)
    {
        verticalMovement = 0;
    }
    
    verticalMovement *= fourBarMultiplier;
    left4Bar.move_velocity(verticalMovement);
    right4Bar.move_velocity(verticalMovement);
    
}