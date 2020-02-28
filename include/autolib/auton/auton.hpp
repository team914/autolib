#pragma once

#include "okapi/api.hpp"
#include "autolib/robot/robot.hpp"
#include "autolib/controller/driveController.hpp"
#include <memory>
#include <map>
#include <string>

namespace autolib{

using namespace okapi;

class Auton{
    public:
    Auton();
    Auton( lv_obj_t * iparent = lv_scr_act() );
    Auton( lv_obj_t * iparent = lv_scr_act(), lv_color_t icolor = LV_COLOR_GRAY );

    void add( const std::string &id, std::function< void()> iroutine );
    void run( const std::string &id );

    private:
    std::map<std::string, std::function<void()>> routines;

    lv_obj_t * parent;
    lv_color_t color;
    bool display {false};
    static lv_res_t btnm_action(lv_obj_t * btnm, const char *txt);
};

}//autolib