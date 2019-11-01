#include "autolib/controller/driveController.hpp"

#include "main.h"
namespace autolib{

using namespace okapi;

DriveController::DriveController( const std::shared_ptr<OdomChassisController> &ichassis, const std::shared_ptr<ThreeEncoderSkidSteerModel> &imodel ):
        chassis(ichassis),
        model(imodel),
        task(taskFnc, this, "Drive Controller"){
  double maxVel = 1.5239828296; //http://www.endmemo.com/physics/rpmlinear.php
  double maxAccel = maxVel * 2;
  double maxJerk = maxAccel / 4;

  pathfinder = AsyncMotionProfileControllerBuilder()
    .withOutput( model, chassis->getChassisScales(), AbstractMotor::GearsetRatioPair( AbstractMotor::gearset::green, 5/3 )  )
    .withLimits( PathfinderLimits{ maxVel, 5, 1 } )
//    .withTimeUtilFactory( TimeUtilFactory::create() )
    .withLogger( Logger::getDefaultLogger() )
    .buildMotionProfileController();

  leftAccelTimer.placeMark();
  leftJerkTimer.placeMark();

  leftVelocity.push_back(0);
  leftAccel.push_back(0);
  leftJerk.push_back(0);
}

void DriveController::drive( double ileft, double iright, double scale, double diff ){
  left = ileft * scale;
  right = iright * scale;
}

double DriveController::getLeftVelocity(){
  isRun = false;
  double velocity = model->getLeftSideMotor()->getActualVelocity() * (chassis->getChassisScales().wheelDiameter.convert( meter ) /2);
  isRun = true;

  leftVelocity.push_back(velocity);
  return velocity;
}

double DriveController::getLeftAccel(){
  double dt = leftAccelTimer.getDtFromMark().convert(second);

  double accel = (leftVelocity.back() - leftVelocity.at( leftVelocity.size() - 2 )) / dt;

  leftAccelTimer.clearMark();
  leftAccelTimer.placeMark();

  leftAccel.push_back(accel);
  return accel;
}

double DriveController::getLeftJerk(){
  double dt = leftJerkTimer.getDtFromMark().convert(second);

  double jerk = (leftAccel.back() - leftAccel.at( leftAccel.size() - 2 )) / dt;

  leftJerkTimer.clearMark();
  leftJerkTimer.placeMark();

  leftJerk.push_back(jerk);
  return jerk;
}

double DriveController::getRightVelocity(){
  isRun = false;
  double ivelocity = model->getRightSideMotor()->getActualVelocity();
  isRun = true;
  return ivelocity;
}

std::shared_ptr<OdomChassisController> DriveController::getChassis(){
  isRun = false;
  return chassis;
}

std::shared_ptr<ThreeEncoderSkidSteerModel> DriveController::getModel(){
  isRun = false;
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
