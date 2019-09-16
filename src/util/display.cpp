#include "autolib/util/display.hpp"
#include <stdlib.h>

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
