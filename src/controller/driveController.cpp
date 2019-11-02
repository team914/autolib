#include "autolib/controller/driveController.hpp"

#include "main.h"
namespace autolib{

using namespace okapi;

DriveController::DriveController( const std::shared_ptr<ChassisController> &ichassis, const bool &iisOdom ):
        chassis(ichassis),
        model(ichassis->getModel()),
        isOdom(iisOdom),
        task(taskFnc, this, "Drive Controller"){
  if( iisOdom )
    odom = std::static_pointer_cast<OdomChassisController>( ichassis );
}

void DriveController::drive( double ileft, double iright, double scale, double maxVelocity ){
  setLeftVelocity = (ileft / maxVelocity) * scale;
  setRightVelocity = (iright / maxVelocity) * scale;
}

std::shared_ptr<ChassisController> DriveController::getChassis(){
  lock();
  return chassis;
}

std::shared_ptr<OdomChassisController> DriveController::getOdom(){
  lock();
  if( isOdom )
    return odom;
  else{
    printf("DriveController getOdom: Warning you can't get the odom chassis controller if you didn't initialize this class with setting iisOdom = true\n");
  }
  return odom;
}

std::shared_ptr<ChassisModel> DriveController::getModel(){
  lock();
  return model;
}

void DriveController::lock(){
  isRun = false;
}

void DriveController::unlock(){
  isRun = true;
}

void DriveController::run(){
  while(true){
    if( isRun ){
      model->left( setLeftVelocity );
      model->right( setRightVelocity );
    }
    pros::delay(20);    
  }
}

void DriveController::taskFnc( void * in ){
  pros::delay(100);
  DriveController* out = static_cast<DriveController*>( in );
  out->run();
}

}//autolib
