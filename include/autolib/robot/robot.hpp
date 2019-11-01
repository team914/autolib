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

    static std::shared_ptr<DriveController> makeDrive(

    );

};

}//autolib