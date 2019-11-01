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

std::shared_ptr<OdomChassisController> Robot::makeChassis(
        std::shared_ptr<ADIEncoder> leftEncoder,
        std::shared_ptr<ADIEncoder> rightEncoder,
        std::shared_ptr<ADIEncoder> middleEncoder,
        MotorGroup leftMotors, 
        MotorGroup rightMotors
        ChassisScales scales){
    return ChassisControllerBuilder()
        .withMotors(
            leftMotors,
            rightMotors
        )
        .withOdometry()
        .buildOdometry();
    }
}

std::shared_ptr<ThreeEncoderSkidSteerModel> Robot::makeModel(
        std::shared_ptr<OdomChassisController> chassis){
    return std::dynamic_pointer_cast<ThreeEncoderSkidSteerModel>(chassis->getModel());
}

std::shared_ptr<DriveController> Robot::makeDrive( 
        std::shared_ptr<OdomChassisController> chassis, 
        std::shared_ptr<ThreeEncoderSkidSteerModel> model){
    return std::make_shared<DriveController>( chassis, model );
}

}