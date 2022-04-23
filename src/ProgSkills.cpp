#include "main.h"



void move(double inches, bool forward, double multiplier)
{
    
    double wheelDiameter = 4.00;
    double encoderIn1Inch = 400/(wheelDiameter * PI);
    double targetEncoders = inches * encoderIn1Inch;

    double kp = 0.2;
    double ki = 0.0;
    double kd = 0.0;
    double averageEncoders = 0;
    double averageEncodersRing = 0;
    double lbe, lfe, rbe, rfe;

    double error;
    double errorRing;
    double prevError = 0;
    double errorSum = 0;
    double derivative = 0;

    //reset encoder values:
    frontLeft.tare_position();
    frontRight.tare_position();
    backLeft.tare_position();
    backRight.tare_position();

    
    while(averageEncoders < targetEncoders - 100)
    {
        lbe = backLeft.get_position();
        lfe = frontLeft.get_position();
        rbe = backRight.get_position();
        rfe = frontRight.get_position();

        averageEncoders = fabs((lbe + rfe + rbe + rfe)/4.0);
        error = targetEncoders - averageEncoders;
        derivative = error - prevError;
        errorSum+=error;

        double power = (error*kp + errorSum* ki + derivative* kd)* multiplier;
        if(forward == false)
        {
            power *= -1;
        }
        backLeft.move_velocity(power);
        backRight.move_velocity(power);
        frontLeft.move_velocity(power);
        frontRight.move_velocity(power);
    }
    backLeft.move_velocity(0);
    backRight.move_velocity(0);
    frontLeft.move_velocity(0);
    frontRight.move_velocity(0);
    pros:: delay(10);    
}

void turn(int deg, bool direction)
{
    inertialSensor.tare_rotation();
    deg -= 5;
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
    frontLeft.move_velocity(-10);
    frontRight.move_velocity(-10);
    backLeft.move_velocity(-10);
    backRight.move_velocity(-10);
    pros::delay(10);
    frontLeft.move_velocity(0);
    frontRight.move_velocity(0);
    backLeft.move_velocity(0);
    backRight.move_velocity(0);
    pros::delay(10);
     
}

void moveMogoLift(int encoders, bool dir)
{
    lift.tare_position();
    if(dir == up)
    {
        while(lift.get_position() < encoders)
        {
            lift.move_velocity(100);
        }
    }
    else
    {
        while(lift.get_position() > -encoders)
        {
            lift.move_velocity(-100);
        }
    }
    lift.move_velocity(0);
}

void move4Bar(int encoders, bool dir)
{
    left4Bar.tare_position();
    right4Bar.tare_position();
    if(dir == up)
    {
        while((left4Bar.get_position() < encoders) && (right4Bar.get_position() < encoders))
        {
            left4Bar.move_velocity(100);
            right4Bar.move_velocity(100);
        }
    }
    else
    {
        while((left4Bar.get_position() > -encoders) && (right4Bar.get_position() > -encoders))
        {
            left4Bar.move_velocity(-100);
            right4Bar.move_velocity(-100);
        }
    }
    left4Bar.move_velocity(0);
    right4Bar.move_velocity(0);
}

void moveClamp(bool dir)
{
    clamp.tare_position();
    if(dir == up)
    {
        while(clamp.get_position() < 130)
        {
            clamp.move_velocity(100);
        }
    }
    if(dir == down)
    {
        while(clamp.get_position() > -130)
        {
            clamp.move_velocity(-100);
        }
    }
    clamp.move_velocity(-100);
}

void turnWithEncoder(double degrees, bool direction)
{
    double wheelBase = 10.0;
    double wheelD = 4.00;
    double gearRatio = 1.0;
    double targetEncoder = degrees * wheelBase * gearRatio / wheelD;

    double lb = 0, lf = 0, rb = 0, rf = 0;
    double avgEncoders = 0;
    frontRight.tare_position();
    frontLeft.tare_position();
    backLeft.tare_position();
    backRight.tare_position();
    if(direction == left)
    {
        while(avgEncoders < targetEncoder)
        {
            avgEncoders = (rb + rf)/2.0;
            frontRight.move_velocity(100);
            backRight.move_velocity(100);
            frontLeft.move_velocity(-100);
            backLeft.move_velocity(-100);
        }
    }
    else
    {
        while(avgEncoders < targetEncoder)
        {
            avgEncoders = (lb + lf)/2.0;
            frontLeft.move_velocity(100);
            backLeft.move_velocity(100);
            frontRight.move_velocity(-100);
            backRight.move_velocity(-100);
        }
    }
    }


void progSkill()
{
    const int FourBarEncoders = 300;
    const int LiftEncoders = 200;
    
    inertialSensor.reset(); 
    //Pick up red mogo
    // backward(12);
    // moveMogoLift(LiftEncoders, up);
    // forward(2);
    // turn(90, right); //turn right 90 degrees to face neutral mogo
    // forward(50); //move forward to yellow 
    // moveClamp(down);
    // move4Bar(FourBarEncoders, up);// pick up yellow neutral mogo
    // turn(45,right); //heading toward left side of platform
    // forward(54); // go to platform
    // moveClamp(up); //drop neutral mogo
    // turn(45,right); 
    // move4Bar(FourBarEncoders, down); //lower 4bar
    // moveMogoLift(LiftEncoders, down); //let go of red mogo
    // forward(12);
    // turn(90, right); //get ready for neutral
    // forward(48); //go to neutral mogo
    // moveClamp(down);
    // move4Bar(FourBarEncoders, up);
    // forward(48); // go to platform
    // moveClamp(down);//drop neutral mogo
    // turn(90, left);
    // move4Bar(FourBarEncoders, down);

    //forward(50.0);
        //move(66.5, true, 2.0);
    move(60.5, true, 6.0);
    pros::delay(500);
    moveClamp(down);
    move(45.0, false, 12.0);
    moveClamp(up);
    clamp.move_velocity(0);
    pros::delay(10);

}