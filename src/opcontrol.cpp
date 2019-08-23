#include "main.h"
#include "okapi/api.hpp"
#include "okapi/pathfinder/include/pathfinder.h"
#include "autolib/api.hpp"

std::shared_ptr<OdomChassisController> drive;
std::shared_ptr<ChassisController> finder;

void printSensorVals(void *) {
  while (true) {
    // auto state = drive->model().getSensorVals();
    // printf("left: %ld, right: %ld\n", state[0], state[1]);
    auto state = drive->getState(StateMode::FRAME_TRANSFORMATION);
    printf("x=%f, y=%f, theta=%f\n",
           state.x.convert(inch),
           state.y.convert(inch),
           state.theta.convert(degree));
    pros::delay(50);
  }
}

void opcontrol() {
  printf("asdf\n");
  pros::delay(100);

  Logger::setDefaultLogger(
    std::make_shared<Logger>(std::make_unique<Timer>(), "/ser/sout", Logger::LogLevel::debug));

  drive = ChassisControllerBuilder()
            .withMotors({-18, 19, 20}, {16, -17, -14})
            .withDimensions({{4.1_in, 11.375_in}, imev5GreenTPR})
            .withMaxVelocity(100)
            .withOdometry()
            .buildOdometry();
            // .withDimensions({{3.125_in, 11.375_in}, 4096})
            // .withGains({0.006, 0, 0.0001}, {0.006, 0, 0.0001})
            // .withSensors({'G', 'H'}, {'E', 'F'})
            //            .withLogger(std::make_shared<Logger>(
            //              std::make_unique<Timer>(), "/ser/sout", Logger::LogLevel::debug))
/*
  autolib::PathGenerator pathGenerator( {1.0, 2.0, 4.0} );
  pathGenerator.generatePath( 
    { okapi::Point{ 1_ft, 1_ft, 270_deg }, okapi::Point{ 1_ft, 0_ft, 90_deg } }, 
    std::string("test")
  );

  autolib::PurePursuit ( {1.0, 2.0, 4.0} );
//*/


  //  pros::Task printSensorValsTask(printSensorVals);

  //  drive->moveDistance(6_in);
  //  drive->turnAngle(90_deg);
  //  drive->moveDistance(6_in);

  while (true) {
    pros::delay(50);
  }
}
