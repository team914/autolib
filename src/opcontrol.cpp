#include "main.h"
#include "okapi/api.hpp"
#include "okapi/pathfinder/include/pathfinder.h"
#include "autolib/api.hpp"

using namespace autolib;

std::shared_ptr<OdomChassisController> controller;
std::shared_ptr<ChassisModel> model;

void opcontrol() {

  Logger::setDefaultLogger(
    std::make_shared<Logger>(std::make_unique<Timer>(), "/ser/sout", Logger::LogLevel::debug));

  controller = ChassisControllerBuilder()
  	.withMotors({1, -2}, {-6, 7})
  	.withSensors( IntegratedEncoder{ 1 }, IntegratedEncoder{ 6, true } )
	  .withOdometry( StateMode::FRAME_TRANSFORMATION )
  	.withGearset( AbstractMotor::GearsetRatioPair{ AbstractMotor::gearset::green, 5/3 } )
	  .withDimensions( {{3.75_in, 15_in}, 900} )
	  .buildOdometry();
	
  model = controller->getModel();

  PathGenerator pathGenerator( {1.0, 2.0, 4.0} );
  pathGenerator.generatePath( 
    { 
		Pose{ 1_ft, 1_ft, 270_deg }, 
		Pose{ 1_ft, 0_ft, 90_deg } 
	}, 
    std::string("test")
  );

  autolib::PurePursuit purePursuit( pathGenerator.getPaths(), 1_ft );
  auto state = controller->getState();
  PurePursuitTriangle triangle = purePursuit.run( state, std::string("test") );

  //  pros::Task printSensorValsTask(printSensorVals);

  //  drive->moveDistance(6_in);
  //  drive->turnAngle(90_deg);
  //  drive->moveDistance(6_in);

  while (true) {
    pros::delay(50);
  }
}
