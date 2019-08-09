#include "main.h"
#include "okapi/api.hpp"
#include "autolib/main.hpp"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

using namespace autolib;

void opcontrol() {

	PathGenerator pathGenerator(
	{
		autolib::Point{ -1_ft, 1_ft },
		autolib::Point{ 0_ft, 2_ft },
		autolib::Point{ 1_ft, 1_ft },
		autolib::Point( 1_in, 1_in )
	}, 1_in );

	pathGenerator.generatePath( PathGenerator::PathType::HermiteSpline );

	PurePursuit purePursuit( pathGenerator.getPath(), 4_in );

	purePursuit.getGoalCurvature( 0_ft, 0_in, 0_rad );

	while (true) {
		
	}
}
