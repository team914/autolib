#include "autolib/robot/robot.hpp"

#include "autolib/controller/driveController.hpp"

#include "okapi/api.hpp"

namespace autolib{

Robot::Robot(){}

std::shared_ptr<Controller> Robot::makeController(
        MotorGroup motors,
        const char * id){
    return std::make_shared<Controller>( motors, id );
}


}