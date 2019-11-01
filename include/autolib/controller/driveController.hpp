#pragma once

#include "okapi/api.hpp"
#include <memory>
#include <vector>

namespace autolib{

using namespace okapi;

class DriveController{
    public:

    DriveController( const std::shared_ptr<ChassisController> &ichassis, const std::shared_ptr<ChassisModel> &imodel );

    void drive( double left, double right, double scale = 1, double diff = 1 );

    double getLeftVelocity();
    double getLeftAccel();
    double getLeftJerk();

    double getRightVelocity();

    std::shared_ptr<ChassisController> getChassis();
    std::shared_ptr<ChassisModel> getModel();

    void lock();
    void unlock();

    private:
    double left = 0;
    double right = 0;

    std::shared_ptr<ChassisController> chassis {nullptr};
    std::shared_ptr<ChassisModel> model {nullptr};

    void run();
    bool isRun = true;

    pros::Task task;
    static void taskFnc(void*);

};

}//autolib
