#include "main.h"
//#include "autolib/api.hpp"
#include "odomDebug/odomDebug.hpp"

/*

autolib::Pose startPose{ 1_ft, 3_ft, 90_deg };
bool reverse = true;
double x = -1;
double y = 1;

autolib::Pose pose = startPose;

void setState(OdomDebug::state_t state) {
    // set these values to your odometry
    // to convert the QUnits to doubles, call
    // `x.convert(inch)` or `theta.convert(radian)`
    // you can use any length or angle unit
    pose.x = state.x;
    pose.y = state.y;
    pose.yaw = state.theta;
}

void resetSensors() {
    // reset sensors
    // reset odometry
	pose = startPose;
}

void initialize()
{
	OdomDebug display(lv_scr_act(), LV_COLOR_ORANGE);
	display.setStateCallback(setState);
	display.setResetCallback(resetSensors);

    display.setData({0_in, 0_in, 0_deg}, {0, 0, 0});

}
//*/

lv_color_t RED            = LV_COLOR_RED;
lv_color_t LIGHT_RED      = LV_COLOR_MAKE(255,153,153);
lv_color_t DARK_RED       = LV_COLOR_MAKE(139,0,0);
lv_color_t WHITE          = LV_COLOR_WHITE;
lv_color_t SILVER         = LV_COLOR_SILVER;
lv_color_t GRAY           = LV_COLOR_GRAY;
lv_color_t LIGHT_GRAY     = LV_COLOR_MAKE(64,64,64);
lv_color_t DARK_GRAY      = LV_COLOR_MAKE(160,160,160);
lv_color_t BLACK          = LV_COLOR_BLACK;
lv_color_t YELLOW         = LV_COLOR_YELLOW;
lv_color_t LIGHT_YELLOW   = LV_COLOR_MAKE(255, 255, 153);
lv_color_t DARK_YELLOW    = LV_COLOR_MAKE(204,204,0);
lv_color_t OLIVE          = LV_COLOR_OLIVE;
lv_color_t LIME           = LV_COLOR_LIME;
lv_color_t GREEN          = LV_COLOR_GREEN;
lv_color_t LIGHT_GREEN    = LV_COLOR_MAKE(153,255,153);
lv_color_t DARK_GREEN     = LV_COLOR_MAKE(0,204,0);
lv_color_t CYAN           = LV_COLOR_CYAN;
lv_color_t AQUA           = CYAN;
lv_color_t TEAL           = LV_COLOR_TEAL;
lv_color_t BLUE           = LV_COLOR_BLUE;
lv_color_t LIGHT_BLUE     = LV_COLOR_MAKE(153,153,255);
lv_color_t DARK_BLUE      = LV_COLOR_MAKE(0,0,139);
lv_color_t NAVY           = LV_COLOR_NAVY;
lv_color_t MAGENTA        = LV_COLOR_MAGENTA;
lv_color_t PURPLE         = LV_COLOR_PURPLE;
lv_color_t ORANGE         = LV_COLOR_ORANGE;

bool toggles[3] = { false, false, false };

lv_obj_t * createBtn(lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
    int id, const char * title)
{
    lv_obj_t * btn = lv_btn_create(parent, NULL);
    lv_obj_set_pos(btn, x, y);
    lv_obj_set_size(btn, width, height);
    lv_obj_set_free_num(btn, id);

    lv_obj_t * label = lv_label_create(btn, NULL);
    lv_label_set_text(label, title);
    lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);

    return btn;
}

lv_style_t * createBtnStyle(lv_style_t * copy, lv_color_t rel, lv_color_t pr,
    lv_color_t tglRel, lv_color_t tglPr, lv_color_t tglBorder, lv_color_t textColor, lv_obj_t * btn)
{
    lv_style_t * btnStyle = (lv_style_t *)malloc(sizeof(lv_style_t) * 4);

    for(int i = 0; i < 4; i++) lv_style_copy(&btnStyle[i], copy);

    btnStyle[0].body.main_color = rel;
    btnStyle[0].body.grad_color = rel;
    btnStyle[0].text.color = textColor;

    btnStyle[1].body.main_color = pr;
    btnStyle[1].body.grad_color = pr;
    btnStyle[1].text.color = textColor;

    btnStyle[2].body.main_color = tglRel;
    btnStyle[2].body.grad_color = tglRel;
    btnStyle[2].body.border.width = 2;
    btnStyle[2].body.border.color = tglBorder;
    btnStyle[2].text.color = textColor;

    btnStyle[3].body.main_color = tglPr;
    btnStyle[3].body.grad_color = tglPr;
    btnStyle[3].body.border.width = 2;
    btnStyle[3].body.border.color = tglBorder;
    btnStyle[3].text.color = textColor;

    lv_btn_set_style(btn, LV_BTN_STYLE_REL, &btnStyle[0]);
    lv_btn_set_style(btn, LV_BTN_STYLE_PR, &btnStyle[1]);
    lv_btn_set_style(btn, LV_BTN_STYLE_TGL_REL, &btnStyle[2]);
    lv_btn_set_style(btn, LV_BTN_STYLE_TGL_PR, &btnStyle[3]);

    return btnStyle;
}

lv_style_t * createBlueBtnStyle(lv_obj_t * btn){
    return createBtnStyle( &lv_style_plain, BLUE, LIGHT_BLUE, DARK_BLUE, BLUE, BLACK, WHITE, btn );
}
lv_style_t * createRedBtnStyle(lv_obj_t * btn){
    return createBtnStyle( &lv_style_plain, RED, LIGHT_RED, DARK_RED, RED, BLACK, WHITE, btn );
}

void setBtnStyle(lv_style_t * btnStyle, lv_obj_t * btn)
{
    lv_btn_set_style(btn, LV_BTN_STYLE_REL, &btnStyle[0]);
    lv_btn_set_style(btn, LV_BTN_STYLE_PR, &btnStyle[1]);
    lv_btn_set_style(btn, LV_BTN_STYLE_TGL_REL, &btnStyle[2]);
    lv_btn_set_style(btn, LV_BTN_STYLE_TGL_PR, &btnStyle[3]);
}


//This function is nice to have to toggle a button because the defualt function is not very good.
void btnSetToggled(lv_obj_t * btn, bool toggled)
{
    if(toggled != (lv_btn_get_state(btn) >= 2)) lv_btn_toggle(btn);
}

static lv_res_t btn_click_action(lv_obj_t * btn){
    uint8_t id = lv_obj_get_free_num(btn); //id usefull when there are multiple buttons

    toggles[id] = !toggles[id];
    btnSetToggled(btn, toggles[id]);

    return LV_RES_OK;
}

void initialize(){
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
