#pragma once
#include "display/lvgl.h"


extern lv_color_t RED;
extern lv_color_t LIGHT_RED;
extern lv_color_t DARK_RED;
extern lv_color_t WHITE;
extern lv_color_t SILVER;
extern lv_color_t GRAY;
extern lv_color_t LIGHT_GRAY;
extern lv_color_t DARK_GRAY;
extern lv_color_t BLACK;
extern lv_color_t YELLOW;
extern lv_color_t LIGHT_YELLOW;
extern lv_color_t DARK_YELLOW;
extern lv_color_t OLIVE;
extern lv_color_t LIME;
extern lv_color_t GREEN;
extern lv_color_t LIGHT_GREEN;
extern lv_color_t DARK_GREEN;
extern lv_color_t CYAN;
extern lv_color_t AQUA;
extern lv_color_t TEAL;
extern lv_color_t BLUE;
extern lv_color_t LIGHT_BLUE;
extern lv_color_t DARK_BLUE;
extern lv_color_t NAVY;
extern lv_color_t MAGENTA;
extern lv_color_t PURPLE;
extern lv_color_t ORANGE;

extern bool toggles[];

lv_obj_t * createBtn(lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
    int id, const char * title);

lv_style_t * createBtnStyle(lv_style_t * copy, lv_color_t rel, lv_color_t pr,
    lv_color_t tglRel, lv_color_t tglPr, lv_color_t tglBorder, lv_color_t textColor, lv_obj_t * btn);

lv_style_t * createBlueBtnStyle(lv_obj_t * btn);

lv_style_t * createRedBtnStyle(lv_obj_t * btn);

void setBtnStyle(lv_style_t * btnStyle, lv_obj_t * btn);
