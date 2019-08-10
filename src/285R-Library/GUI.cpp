#include "285R-Library/GUI.hpp"

namespace gui285R
{
  void brainPower (double currAngle)
  {
    std::string currAngleString = std::to_string(currAngle);

    /* Create a new screen and load it
     * Screen can be created from any type object type
     * Now a Page is used which is an objects with scrollable content*/
    lv_obj_t * scr = lv_page_create(NULL, NULL);
    lv_scr_load(scr);

    /*Create a style*/
    static lv_style_t style;
    lv_style_copy(&style, &lv_style_pretty_color);
    style.body.main_color = LV_COLOR_HEX3(0x666);     /*Line color at the beginning*/
    style.body.grad_color =  LV_COLOR_HEX3(0x666);    /*Line color at the end*/
    style.body.padding.hor = 10;                      /*Scale line length*/
    style.body.padding.inner = 8 ;                    /*Scale label padding*/
    style.body.border.color = LV_COLOR_HEX3(0x333);   /*Needle middle circle color*/
    style.line.width = 3;
    style.text.color = LV_COLOR_HEX3(0x333);
    style.line.color = LV_COLOR_RED;                  /*Line color after the critical value*/

    /*Describe the color for the needles*/
    static lv_color_t needle_colors[] = {LV_COLOR_BLUE};

    /*Create a gauge*/
    lv_obj_t * gauge1 = lv_gauge_create(lv_scr_act(), NULL);
    lv_gauge_set_range(gauge1, -360, 360);
    lv_gauge_set_style(gauge1, &style);
    lv_gauge_set_needle_count(gauge1, 1, needle_colors);
    lv_obj_align(gauge1, NULL, LV_ALIGN_CENTER, 0, 20);

    /*Set the values*/
    lv_gauge_set_value(gauge1, 0, currAngle);

    char * placeHolder = new char [currAngleString.length()+1];
    strcpy (placeHolder, currAngleString.c_str());

    lv_obj_t * label = lv_label_create(scr, NULL);                  /*First parameters (scr) is the parent*/
    lv_label_set_text(label, placeHolder);                          /*Set the text*/
    lv_obj_align(label, gauge1, LV_ALIGN_OUT_RIGHT_MID, 50, 0);     /*Align next to the prev. button.*/
  }
}
