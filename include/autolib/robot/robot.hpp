#pragma once

#include "autolib/controller/driveController.hpp"
#include "autolib/controller/controller.hpp"

#include "okapi/api.hpp"

#include <initializer_list>
#include <memory>
#include <vector>

namespace autolib{

using namespace okapi;

class Robot{
    public:
    Robot();

    //change these
    std::shared_ptr<DriveController> drive {nullptr};
    std::shared_ptr<Controller> intake {nullptr};
    std::shared_ptr<Controller> lift {nullptr};
    std::shared_ptr<Controller> other {nullptr};
    std::shared_ptr<Controller> other2 {nullptr};

    static std::shared_ptr<Controller> makeController(
        MotorGroup motors,
        const char * id);

    static std::shared_ptr<OdomChassisController> makeChassis( 
        std::shared_ptr<ADIEncoder> leftEncoder,
        std::shared_ptr<ADIEncoder> rightEncoder,
        std::shared_ptr<ADIEncoder> middleEncoder,
        MotorGroup leftMotors = MotorGroup( {-12, 20} ), 
        MotorGroup rightMotors = MotorGroup( {11, 19} ),
        ChassisScales scales = ChassisScales({3.25_in, 2.75_in, 6_in, 3.25_in}, 360) );

    static std::shared_ptr<ThreeEncoderSkidSteerModel> makeModel(
        std::shared_ptr<OdomChassisController> chassis);

    static std::shared_ptr<DriveController> makeDrive( 
        std::shared_ptr<OdomChassisController> chassis, 
        std::shared_ptr<ThreeEncoderSkidSteerModel> model);

};

}//autolib