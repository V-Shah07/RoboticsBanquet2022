#include "main.h"

bool right = true;
bool left = false;

void PID(int inches)
{
    double wheelDiameter = 4.00;
    double encoderIn1Inch = 360/(wheelDiameter * PI);
    double targetEncoders = inches * encoderIn1Inch;

    double kp = 0.1;
    double ki = 0.0;
    double kd = 0.0;
    double averageEncoders = 0;
    double lbe, lfe, rbe, rfe;

    double error;
    double prevError = 0;
    double errorSum = 0;
    double derivative = 0;

    //reset encoder values:
    frontLeft.tare_position();
    frontRight.tare_position();
    backLeft.tare_position();
    backRight.tare_position();
    while(averageEncoders < targetEncoders)
    {
        lbe = backLeft.get_position();
        lfe = frontLeft.get_position();
        rbe = backRight.get_position();
        rfe = frontRight.get_position();

        averageEncoders = (lbe + rfe + rbe + rfe)/4.0;
        error = targetEncoders - averageEncoders;
        derivative = error - prevError;
        errorSum+=error;

        double power = (error*kp + errorSum* ki + derivative* kd);

        backLeft.move_velocity(power);
        backRight.move_velocity(power);
        frontLeft.move_velocity(power);
        frontRight.move_velocity(power);
    }

}

void turn(int deg, bool direction)
{
    inertialSensor.tare_rotation();
    if(direction == right)
    {
        while(inertialSensor.get_rotation() < deg)
        {
            frontLeft.move_velocity(100);
            backLeft.move_velocity(100);
            frontRight.move_velocity(-100);
            backRight.move_velocity(-100);
        }
    }
    else
    {
        while(inertialSensor.get_rotation() > -deg)
        {
            frontLeft.move_velocity(-100);
            backLeft.move_velocity(-100);
            frontRight.move_velocity(100);
            backRight.move_velocity(100);           
        }
    }
}
void progSkill()
{
    inertialSensor.reset();
    

}