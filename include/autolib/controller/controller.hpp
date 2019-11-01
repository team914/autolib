#pragma once

#include "okapi/api.hpp"

namespace autolib{

using namespace okapi;

class Controller{
    public:
    Controller( const MotorGroup &imotor, const char * id );

    void moveVelocity( double ivelocity );
    double getVelocity();

    void setBrakeMode( AbstractMotor::brakeMode ibrake );
    void setGearing( AbstractMotor::gearset igearset );

    private:
    double velocity;
    MotorGroup motor;

    void run();
    bool isRun = true;

    pros::Task task;
    static void taskFnc(void*);
};

}//autolib
