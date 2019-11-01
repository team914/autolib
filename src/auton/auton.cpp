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

}//autolib
