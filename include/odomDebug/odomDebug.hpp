#pragma once
#include "main.h"
#include "okapi/api.hpp"

class OdomDebug {

public:

  /**
   * Contains robot state - x, y, theta
   * Can be initialized using QUnits or doubles
   */
  struct state_t {
    QLength x {0.0};
    QLength y {0.0};
    QAngle theta {0.0};

    /** 
     * @param ix QLength
     * @param iy QLength
     * @param itheta QAngle
     */ 
    state_t(QLength ix, QLength iy, QAngle itheta);

    /** 
     * @param ix inches
     * @param iy inches
     * @param itheta radians
     */ 
    state_t(double ix, double iy, double itheta);
  };

  /**
   * Contains encoder information - left, right, middle(optional)
   * Can be initialized using three or two sensors
   */
  struct sensors_t {
    double left {0.0};
    double right {0.0};
    double middle {0.0};

    /**
     * @param ileft the left encoder value
     * @param iright the right encoder value
     */
    sensors_t(double ileft, double iright);

    /**
     * @param ileft the left encoder value
     * @param iright the right encoder value
     * @param imiddle imiddle the middle encoder value
     */
    sensors_t(double ileft, double iright, double imiddle);

  private:
    bool hasMiddle {false};
    friend class OdomDebug;
  };


  /**
   * Constructs the OdomDebug object.
   * @param parent the lvgl parent, color is inherited
   */
  OdomDebug(lv_obj_t* parent);

  /**
   * Constructs the OdomDebug object.
   * @param parent the lvgl parent
   * @param mainColor The main color for the display
   */
  OdomDebug(lv_obj_t* parent, lv_color_t mainColor);

  ~OdomDebug();

  /**
   * Sets the function to be called when a tile is pressed
   * @param callback a function that sets the odometry state
   */
  void setStateCallback(std::function<void(state_t state)> callback);

  /**
   * Sets the function to be called when the reset button is pressed
   * @param callback a function that resets the odometry and sensors
   */
  void setResetCallback(std::function<void()> callback);

  /**
   * Sets the position of the robot in QUnits and puts the sensor data on the display
   * @param state   robot state - x, y, theta
   * @param sensors encoder information - left, right, middle (optional)
   */
  void setData(state_t state, sensors_t sensors);


private:

  // parent container
  lv_obj_t* container = nullptr; 
  lv_style_t cStyle;

  // field
  lv_style_t fStyle; 
  double fieldDim = 0; // width and height of field container

  // tile styles
  lv_style_t grey;
  lv_style_t red;
  lv_style_t blue;

  // robot point
  lv_obj_t* led = nullptr; 
  lv_style_t ledStyle;

  // robot line
  lv_obj_t* line = nullptr; 
  lv_style_t lineStyle;
  std::vector<lv_point_t> linePoints = {{0, 0}, {0, 0}}; // line positions
  int lineWidth = 0;
  int lineLength = 0;

  // status label
  lv_obj_t* statusLabel = nullptr;
  lv_style_t textStyle;

  // reset button styles
  lv_style_t resetRel;
  lv_style_t resetPr;

  // external callbacks to interface with odometry
  std::function<void(state_t state)> stateFnc = nullptr;
  std::function<void()> resetFnc = nullptr;

  static lv_res_t tileAction(lv_obj_t*); // action when tile is pressed
  static lv_res_t resetAction(lv_obj_t*); // action when reset button is pressed

};

