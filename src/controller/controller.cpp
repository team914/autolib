#include "autolib/controller/controller.hpp"

namespace autolib{

Controller::Controller( const MotorGroup &imotor, const char * id ):
    motor(imotor),
    task( taskFnc, this, id ){}

void Controller::moveVelocity(double ivelocity){
    velocity = ivelocity;
}

double Controller::getVelocity(){
    isRun = false;
    double ivelocity = motor.getActualVelocity();
    isRun = true;
    return ivelocity;
}

void Controller::run(){
    while(true){
        if( isRun ){
            motor.moveVelocity( velocity );
            pros::delay(20);
        }else
            pros::delay(20);        
    }
}

void Controller::taskFnc(void * in){
    pros::delay(100);
    Controller* out = static_cast<Controller*>( in );
    out->run();
}

}//autolib
