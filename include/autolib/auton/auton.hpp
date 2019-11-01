#pragma once

#include "okapi/api.hpp"
#include "idp/robotConfig.hpp"
#include "idp/controller/driveController.hpp"
#include <memory>
#include <map>
#include <string>

namespace autolib{

using namespace okapi;

class Auton{
    public:
    Auton( const std::shared_ptr<Robot> &irobot );

    void add( const std::string &id, std::function< void(std::shared_ptr<Robot>)> iroutine );
    void run( const std::string &id );

    static void execute( std::shared_ptr<Robot> robot, const char * id );
    static void forward( std::shared_ptr<Robot> robot, QLength length, const char * id );
    static void turn( std::shared_ptr<Robot> robot, QAngle angle, const char * id );
    static void vector( std::shared_ptr<Robot> robot, QLength length, QAngle angle, const char * id );

    private:
    const std::shared_ptr<Robot> robot { nullptr };
    std::map<std::string, std::function<void(std::shared_ptr<Robot>)>> routines;
};

}//autolib