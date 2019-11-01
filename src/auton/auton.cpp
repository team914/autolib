#include "autolib/auton/auton.hpp"

#include "autolib/robot/robot.hpp"

namespace autolib{

using namespace okapi;

Auton::Auton( const std::shared_ptr<Robot> &irobot ):
        robot(irobot){
    printf("Auton add: Auton Class Initialized\n");
}

void Auton::add( const std::string &id, std::function<void(std::shared_ptr<Robot>)> routine ){
    printf("Auton add: Added Routine\n");
    routines.insert( {id, routine} );
}

void Auton::run( const std::string &id ){
    std::cout << "Auton run: Running Auto " << id.c_str() << ".\n";
    std::function<void(std::shared_ptr<Robot>)> routine = routines.at(id);
    routine( robot );
}
//*
void Auton::execute( std::shared_ptr<Robot> robot, const char * id ){
	auto pathfinder = robot->drive->getPathfinder();
	pathfinder->setTarget(id);
	pathfinder->waitUntilSettled();
}

void Auton::forward( std::shared_ptr<Robot> robot, QLength length, const char * id ){
	auto pathfinder = robot->drive->getPathfinder();
	pathfinder->generatePath(
		{
			{ 0_ft, 0_ft, 0_deg },
			{ 0_ft, length, 0_deg }
		},
		id
	);
	execute(robot, id);
}

void Auton::turn( std::shared_ptr<Robot> robot, QAngle angle, const char * id ){
	auto pathfinder = robot->drive->getPathfinder();
	pathfinder->generatePath(
		{
			{ 0_ft, 0_ft, 0_deg },
			{ 0_ft, 0_ft, angle }
		},
		id
	);
	execute(robot, id);
}

void Auton::vector( std::shared_ptr<Robot> robot, QLength length, QAngle angle, const char * id ){
	auto pathfinder = robot->drive->getPathfinder();
	pathfinder->generatePath(
		{
			{ 0_ft, 0_ft, 0_deg },
			{ 0_ft, length, angle }
		},
		id
	);
	execute(robot, id);
}

}//autolib
