#pragma once

#include "okapi/api.hpp"
#include <memory>
#include <vector>

namespace autolib{

using namespace okapi;

class DriveController{
    public:

    DriveController( const std::shared_ptr<OdomChassisController> &iodom, const std::shared_ptr<ThreeEncoderSkidSteerModel> &imodel );

    void drive( double left, double right, double scale = 1, double diff = 1 );

    double getLeftVelocity();
    double getLeftAccel();
    double getLeftJerk();

    double getRightVelocity();

    std::shared_ptr<OdomChassisController> getChassis();
    std::shared_ptr<ThreeEncoderSkidSteerModel> getModel();

    void lock();
    void unlock();

    private:
    double left = 0;
    double right = 0;

    std::vector<double> leftVelocity;
    std::vector<double> leftAccel;
    std::vector<double> leftJerk;

    Timer leftAccelTimer;
    Timer leftJerkTimer;

    std::shared_ptr<OdomChassisController> chassis {nullptr};
    std::shared_ptr<ThreeEncoderSkidSteerModel> model {nullptr};

    void run();
    bool isRun = true;

    pros::Task task;
    static void taskFnc(void*);

};

}//autolib
