#include "autolib/controller/driveController.hpp"

#include "main.h"
namespace autolib{

using namespace okapi;

DriveController::DriveController( const std::shared_ptr<ChassisController> &ichassis, const std::shared_ptr<ChassisModel> &imodel ):
        chassis(ichassis),
        model(imodel),
        task(taskFnc, this, "Drive Controller"){
}

void DriveController::drive( double ileft, double iright, double scale, double diff ){
  left = ileft * scale;
  right = iright * scale;
}

std::shared_ptr<ChassisController> DriveController::getChassis(){
  lock();
  return chassis;
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
      model->left( left );
      model->right( right );
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
