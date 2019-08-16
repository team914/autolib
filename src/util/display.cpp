
#include "autolib/util/display.hpp"

Display::Display(lv_obj_t* parent, autolib::Pose &istartPose )
: Display(parent, lv_obj_get_style(parent)->body.main_color, istartPose) {}

Display::Display(lv_obj_t* parent, lv_color_t mainColor, autolib::Pose &istartPose) :
container(lv_obj_create(parent, NULL)), startPose(istartPose), pose(istartPose), task(taskFnc, this)
{
  lv_obj_set_size(container, lv_obj_get_width(parent), lv_obj_get_height(parent));
  lv_obj_align(container, NULL, LV_ALIGN_CENTER, 0, 0);

  lv_style_t* cStyle = new lv_style_t;
  lv_style_copy(cStyle, &lv_style_plain_color);
  cStyle->body.main_color = mainColor;
  cStyle->body.grad_color = mainColor;
  cStyle->body.border.width = 0;
  cStyle->body.radius = 0;
  lv_obj_set_style(container, cStyle);

  /**
  * Field
  */
  {
    field = lv_obj_create(container, NULL);
    fieldDim = std::min(lv_obj_get_width(container), lv_obj_get_height(container));
    lv_obj_set_size(field, fieldDim, fieldDim);
    lv_obj_align(field, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0);

    lv_style_t* fStyle = new lv_style_t;
    lv_style_copy(fStyle, cStyle);
    fStyle->body.main_color = LV_COLOR_WHITE;
    fStyle->body.grad_color = LV_COLOR_WHITE;
    lv_obj_set_style(field, fStyle);

    lv_style_t* grey = new lv_style_t;
    lv_style_t* red = new lv_style_t;
    lv_style_t* blue = new lv_style_t;
    lv_style_copy(grey, &lv_style_plain);
    grey->body.main_color = LV_COLOR_HEX(0x828F8F);
    grey->body.grad_color = LV_COLOR_HEX(0x828F8F);
    grey->body.border.width = 1;
    grey->body.radius = 0;
    grey->body.border.color = LV_COLOR_WHITE;
    lv_style_copy(red, grey);
    red->body.main_color = LV_COLOR_HEX(0xD42630);
    red->body.grad_color = LV_COLOR_HEX(0xD42630);
    lv_style_copy(blue, grey);
    blue->body.main_color = LV_COLOR_HEX(0x0077C9);
    blue->body.grad_color = LV_COLOR_HEX(0x0077C9);

    std::vector<std::vector<lv_style_t*>> data = {
      {grey, red , grey, grey, blue, grey},
      {red , grey, grey, grey, grey, blue},
      {grey, grey, grey, grey, grey, grey},
      {grey, grey, grey, grey, grey, grey},
      {grey, grey, grey, grey, grey, grey},
      {grey, grey, grey, grey, grey, grey}
    };

    double tileDim = fieldDim / data.size();

    for(double y = 0; y < 6; y++) {
      for(double x = 0; x < 6; x++) {
        lv_obj_t* tileObj = lv_btn_create(field, NULL);
        lv_obj_set_pos(tileObj, x * tileDim, y * tileDim);
        lv_obj_set_size(tileObj, tileDim, tileDim);
        lv_btn_set_action(tileObj, LV_BTN_ACTION_CLICK, tileAction);
        lv_obj_set_free_num(tileObj, y * 6 + x);
        lv_obj_set_free_ptr(tileObj, this);
        lv_btn_set_toggle(tileObj, false);
        lv_btn_set_style(tileObj, LV_BTN_STYLE_PR, data[y][x]);
        lv_btn_set_style(tileObj, LV_BTN_STYLE_REL, data[y][x]);
      }
    }
  }

  /**
  * Reset Button
  */
  {
    lv_obj_t* btn = lv_btn_create(container, NULL);
    lv_obj_set_size(btn, 100, 40);
    lv_obj_align(btn, NULL, LV_ALIGN_IN_TOP_MID, -lv_obj_get_width(container)/2 + (lv_obj_get_width(container) - fieldDim)/2, 0);
    lv_obj_set_free_ptr(btn, this);
    lv_btn_set_action(btn, LV_BTN_ACTION_PR, resetAction);

    lv_style_t* btnm_rel = new lv_style_t;
    lv_style_copy(btnm_rel, &lv_style_btn_tgl_rel);
    btnm_rel->body.main_color = mainColor;
    btnm_rel->body.grad_color = mainColor;
    btnm_rel->body.border.color = LV_COLOR_WHITE;
    btnm_rel->body.border.width = 2;
    btnm_rel->body.border.opa = LV_OPA_100;
    btnm_rel->body.radius = 2;
    btnm_rel->text.color = LV_COLOR_WHITE;

    lv_style_t* btnm_pr = new lv_style_t;
    lv_style_copy(btnm_pr, btnm_rel);
    btnm_pr->body.main_color = LV_COLOR_WHITE;
    btnm_pr->body.grad_color = LV_COLOR_WHITE;
    btnm_pr->text.color = mainColor;

    lv_btn_set_style(btn, LV_BTN_STYLE_REL, btnm_rel);
    lv_btn_set_style(btn, LV_BTN_STYLE_PR, btnm_pr);

    /**
    * Reset Button Label
    */
    lv_obj_t* label = lv_label_create(btn, NULL);
    lv_style_t* style = new lv_style_t;
    lv_style_copy(style, &lv_style_plain);
    style->text.color = LV_COLOR_WHITE;
    style->text.opa = LV_OPA_100;
    lv_obj_set_style(label, style);
    lv_label_set_text(label, "Reset");
  }


}

Display::~Display() {
  lv_obj_del(container);
}

lv_res_t Display::tileAction(lv_obj_t* tileObj) {
  Display* that = static_cast<Display*>(lv_obj_get_free_ptr(tileObj));
  int num = lv_obj_get_free_num(tileObj);
  int y = num / 6;
  int x = num - y * 6;
  that->pose = autolib::Pose{x * tile + 0.5_tl, 1_crt - y * tile - 0.5_tl, 0_deg};
  return LV_RES_OK;
}


lv_res_t Display::resetAction(lv_obj_t* btn) {
  Display* that = static_cast<Display*>(lv_obj_get_free_ptr(btn));
  that->pose = that->startPose;
  return LV_RES_OK;
}

void Display::changePose( autolib::Pose &ipose ){
  pose = ipose;
}

void Display::run() {

  lv_color_t mainColor = lv_obj_get_style(container)->body.main_color;

  lv_obj_t* led = lv_led_create(field, NULL);
  lv_led_on(led);
  lv_obj_set_size(led, fieldDim / 15, fieldDim / 15);

  lv_style_t ledStyle;
  lv_style_copy(&ledStyle, &lv_style_plain);
  ledStyle.body.radius = LV_RADIUS_CIRCLE;
  ledStyle.body.main_color = mainColor;
  ledStyle.body.grad_color = mainColor;
  ledStyle.body.border.color = LV_COLOR_WHITE;
  ledStyle.body.border.width = 2;
  ledStyle.body.border.opa = LV_OPA_100;
  lv_obj_set_style(led, &ledStyle);

  std::vector<lv_point_t> points = {{0, 0}, {0, 0}};

  lv_obj_t* arrow = lv_line_create(field, NULL);
  lv_line_set_points(arrow, points.data(), points.size());
  lv_obj_set_pos(arrow, 0, 0);

  lv_style_t arrowStyle;
  lv_style_copy(&arrowStyle, &lv_style_plain);
  int lineWidth = 3;
  arrowStyle.line.width = lineWidth;
  arrowStyle.line.opa = LV_OPA_100;
  arrowStyle.line.color = mainColor;
  lv_obj_set_style(arrow, &arrowStyle);

  int arrowHeight = fieldDim / 6;

  lv_obj_t* label = lv_label_create(container, NULL);
  lv_style_t textStyle;
  lv_style_copy(&textStyle, &lv_style_plain);
  textStyle.text.color = LV_COLOR_WHITE;
  textStyle.text.opa = LV_OPA_100;
  lv_obj_set_style(label, &textStyle);

  while(true) {

    double x = pose.x.convert(court);
    double y = pose.y.convert(court);
    double yaw = pose.yaw.convert(radian);

    lv_obj_set_pos(led, (x * fieldDim) - lv_obj_get_width(led)/2, (y * fieldDim) - lv_obj_get_height(led)/2 - 1);

    points[0] = {(int16_t)((x * fieldDim)), (int16_t)((y * fieldDim) - (lineWidth/2))};
    double newY = arrowHeight * cos(yaw);
    double newX = arrowHeight * sin(yaw);
    points[1] = {(int16_t)(newX + points[0].x), (int16_t)(-newY + points[0].y)};

    lv_line_set_points(arrow, points.data(), points.size());
    lv_obj_invalidate(arrow);

    std::string text =
    "X: " + std::to_string(pose.x.convert(foot)) + "\n" +
    "Y: " + std::to_string(pose.y.convert(foot)) + "\n" +
    "Theta: " + std::to_string(pose.yaw.convert(degree)) + "\n";
    lv_label_set_text(label, text.c_str());
    lv_obj_align(label, container, LV_ALIGN_CENTER, -lv_obj_get_width(container)/2 + (lv_obj_get_width(container) - fieldDim)/2, 0);

    pros::delay(50);
  }
}

void Display::taskFnc(void* input) {
  pros::delay(500);
  Display* that = static_cast<Display*>(input);
  that->run();
}
