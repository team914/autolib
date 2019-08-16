#pragma once
#include "autolib/util/messages.hpp"
#include "display/lvgl.h"
#include "okapi/api.hpp"

class Display {
  public:

  lv_obj_t* container = nullptr;
  autolib::Pose pose;
  autolib::Pose startPose;

  lv_obj_t* field = nullptr;
  double fieldDim = 0;

  pros::Task task;

  Display(lv_obj_t*, autolib::Pose &istartPose );
  Display(lv_obj_t*, lv_color_t, autolib::Pose &istartPose );
  ~Display();

  static lv_res_t tileAction(lv_obj_t*);
  static lv_res_t resetAction(lv_obj_t*);
  static lv_res_t btnmAction(lv_obj_t*);

  void changePose( autolib::Pose &ipose );
  void run();
  static void taskFnc(void*);

};

namespace okapi{
  constexpr QLength tile = 2 * foot;
  constexpr QLength court = 12 * foot;
  inline namespace literals {
    constexpr QLength operator"" _tl(long double x) {
      return static_cast<double>(x) * tile;
    }
    constexpr QLength operator"" _crt(long double x) {
      return static_cast<double>(x) * court;
    }
    constexpr QLength operator"" _tl(unsigned long long int x) {
      return static_cast<double>(x) * tile;
    }
    constexpr QLength operator"" _crt(unsigned long long int x) {
      return static_cast<double>(x) * court;
    }
  }
}//okapi