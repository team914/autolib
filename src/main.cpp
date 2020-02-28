#include "main.h"

#include "autolib/api.hpp"
#include "okapi/api.hpp"

using namespace autolib;

std::shared_ptr<OdomChassisController> chassis;
std::shared_ptr<MotorGroup> intake;
std::shared_ptr<MotorGroup> tray;
std::shared_ptr<MotorGroup> lift;

std::shared_ptr<Auton> auton;

std::function<void()> red1(){}
std::function<void()> red2(){}

std::function<void()> blue1(){}
std::function<void()> blue2(){}

void initialize() {

	//use chassis controller builder
	chassis = okapi::ChassisControllerBuilder()
		.withMotors( 
			okapi::MotorGroup( { -11, 12 } ),
			okapi::MotorGroup( { 19, 20 } )
		)
		//.withSensors()
		//.withGains()
		.withOdometry()
		//.withDerivativeFilters()
		.withDimensions( 
			okapi::AbstractMotor::GearsetRatioPair{ okapi::AbstractMotor::gearset::green, 1.6666667 },
			{ 2.25_in, 13_in }
		)
		.withMaxVelocity( 200 )
		.withMaxVoltage( 14000 )
		//.withOdometryTimeUtilFactory()
		.buildOdometry();

	intake = std::make_shared<okapi::MotorGroup>( MotorGroup( { 2, -9 } ) );
	tray = std::make_shared<okapi::MotorGroup>( MotorGroup( { -1, 10 } ) );
	lift = std::make_shared<okapi::MotorGroup>( MotorGroup( { 5, -6 } ) );

	auton = std::make_shared<Auton>();
	auton->add( "red1", red1() );
	auton->add( "red2", red2() );
	auton->add( "blue1", blue1() );
	auton->add( "blue2", blue2() );

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
