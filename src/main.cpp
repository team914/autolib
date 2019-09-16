#include "main.h"
#include "autolib/api.hpp"
#include "autolib/util/display.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

//This function is nice to have to toggle a button because the defualt function is not very good.

using namespace autolib;

static void btnSetToggled(lv_obj_t * btn, bool toggled)
{
    if(toggled != (lv_btn_get_state(btn) >= 2)) lv_btn_toggle(btn);
}
     
static lv_res_t btn_click_action(lv_obj_t * btn)
{
    uint8_t id = lv_obj_get_free_num(btn); //id usefull when there are multiple buttons

    toggles[id] = !toggles[id];
    btnSetToggled(btn, toggles[id]);

    return LV_RES_OK;
}

void initialize() {
    lv_obj_t * btn = createBtn( lv_scr_act(), 0, 0, 100, 100, 0, "test" );
    lv_obj_t * btn2 = createBtn( lv_scr_act(), 100, 0, 100, 100, 1, "red" );
    lv_obj_t * btn3 = createBtn( lv_scr_act(), 200, 0, 100, 100, 2, "blue" );

    lv_style_t * style = createBtnStyle( &lv_style_plain, YELLOW, LIGHT_YELLOW, GREEN, LIGHT_GREEN, BLACK, WHITE, btn );
    lv_style_t * style2 = createRedBtnStyle(btn);
    lv_style_t * style3 = createBlueBtnStyle(btn); 

    lv_btn_set_action(btn, LV_BTN_ACTION_CLICK, btn_click_action); //set function to be called on button click
    lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, btn_click_action);
    lv_btn_set_action(btn3, LV_BTN_ACTION_CLICK, btn_click_action);

    setBtnStyle(style, btn);
    setBtnStyle(style2, btn2);
    setBtnStyle(style3, btn3);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	while(true){
		pros::delay(20);
	}
}
