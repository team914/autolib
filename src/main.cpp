#include "main.h"

#include "autolib/api.hpp"
#include "okapi/api.hpp"

using namespace autolib;

std::shared_ptr<Robot> robot;

void initialize() {
	//initialize robot class
	robot = std::make_shared<Robot>();

	//use chassis controller builder
	auto chassis = okapi::ChassisControllerBuilder()
		.withMotors( 
			okapi::MotorGroup( { 11, 12 } ),
			okapi::MotorGroup( { 19, 20 } )
		)
		//.withSensors()
		//.withGains()
		.withOdometry()
		//.withDerivativeFilters()
		.withGearset( okapi::AbstractMotor::gearset::green )
		.withDimensions( okapi::ChassisScales( {2.25_in, 13_in }, imev5GreenTPR ) )
		.withMaxVelocity( 200 )
		.withMaxVoltage( 14000 )
		//.withOdometryTimeUtilFactory()
		.buildOdometry();
	
	//initialize robot's drive controller with chassis
	robot->drive = std::make_shared<DriveController>( chassis );

	//initialize robot's intake
	robot->intake = std::make_shared<autolib::Controller>( okapi::MotorGroup( { -2, 9 } ), "intake" );

	//initialize robot's tray
	robot->other = std::make_shared<autolib::Controller>( MotorGroup( { 1, -10 } ), "tray" );
}

void disabled() {}
void competition_initialize() {}

void autonomous() {

}

void opcontrol() {
	while(true){
		pros::delay(20);
	}
}
