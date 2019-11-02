#include "main.h"
#include "autolib/api.hpp"
#include "autolib/util/display.hpp"

using namespace autolib;

std::shared_ptr<Robot> robot;

void initialize() {
	//initialize robot class
	robot = std::make_shared<Robot>();
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
