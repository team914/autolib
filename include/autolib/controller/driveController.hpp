#pragma once

#include "okapi/api.hpp"
#include <memory>
#include <vector>

namespace autolib{

using namespace okapi;

class DriveController{
    public:
    /**
     * DriveController 
     * 
     * @param  {std::shared_ptr<ChassisController>} ichassis : 
     */
    DriveController( const std::shared_ptr<ChassisController> &ichassis, const bool &iisOdom = false );

    /**
     * The algorithm for this is:
     *   leftSideMotor's  velocity = ( left  / maxVelocity ) * scale
     *   rightSideMotor's velocity = ( right / maxVelocity ) * scale
     * 
     * @param  {double} left        : Desired Left RPM
     * @param  {double} right       : Desired Right RPM
     * @param  {double} scale       : This is multiplied by each input value
     * @param  {double} maxVelocity : Max Velocity for the Motors
     */
    void drive( double left, double right, double scale = 1, double maxVelocity = 200 );

    /**
     * This will return the ChassisController.
     * 
     * Warning: You need to unlock() DriveController to continue using it
     * after calling this method!
     * 
     * @return {std::shared_ptr<ChassisController>}  : 
     */
    std::shared_ptr<ChassisController> getChassis();
    
    /**
     * This will return the ChassisController.
     * 
     * Warning: You need to unlock() DriveController to continue using it
     * after calling this method!
     * 
     * @return {std::shared_ptr<ChassisController>}  : 
     */
    std::shared_ptr<OdomChassisController> getOdom();

    /**
     * This will return the ChassisModel.
     * 
     * Warning: You need to unlock() DriveController to continue using it
     * after calling this method!
     * 
     * @return {std::shared_ptr<ChassisModel>}  : 
     */
    std::shared_ptr<ChassisModel> getModel();

    /**
     * This will stop the async prossess.
     */
    void lock();

    /**
     * This will start the async prossess.
     * 
     * Warning: Do not start this and use a shared model or chassis!
     */
    void unlock();

    private:
    double setLeftVelocity = 0;
    double setRightVelocity = 0;

    bool isOdom { false };
    std::shared_ptr<ChassisModel> model {nullptr};
    std::shared_ptr<ChassisController> chassis {nullptr};
    std::shared_ptr<OdomChassisController> odom {nullptr};

    void run();
    bool isRun = true;

    pros::Task task;
    static void taskFnc(void*);
};

}//autolib
