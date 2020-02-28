#include "autolib/auton/auton.hpp"

namespace autolib{

using namespace okapi;

Auton::Auton(){
    printf("Auton: Auton Class Initialized\n");
}

void Auton::add( const std::string &id, std::function<void()> routine ){
    printf("Auton add: Added Routine\n");
    routines.insert( {id, routine} );
}

void Auton::run( const std::string &id ){
    std::cout << "Auton run: Running Auto " << id.c_str() << ".\n";
    auto routine = routines.at(id);
    routine();
}

}//autolib
