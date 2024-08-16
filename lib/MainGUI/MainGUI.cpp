#include "MainGUI.h"

int MainGUI::point_index = 0;
lv_chart_series_t *MainGUI::ser1 = nullptr;

MainGUI::MainGUI()
{
   
}

void MainGUI::createGUI()
{
    createTopLeftContainer();
    createTopRightContainer();
    createBottomContainer();
}

void MainGUI::createTopLeftContainer()
{
    lv_obj_t *leftContainer = lv_obj_create(lv_scr_act());
    lv_obj_set_size(leftContainer, lv_pct(50), lv_pct(50));
    lv_obj_align(leftContainer, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_obj_t *title_label = lv_label_create(leftContainer);
    lv_label_set_text(title_label, "Settings");
    lv_obj_set_style_text_font(title_label, &lv_font_montserrat_18, 0);
    lv_obj_align(title_label, LV_ALIGN_TOP_MID, 0, 10);

    lv_obj_t *logo = lv_label_create(leftContainer);
    lv_label_set_text(logo, LV_SYMBOL_SETTINGS);
    lv_obj_set_style_text_font(logo, &lv_font_montserrat_24, 0);
    lv_obj_align(logo, LV_ALIGN_TOP_MID, 0, 30);

    lv_obj_t *button = lv_button_create(leftContainer);
    lv_obj_set_size(button, 80, 30);
    lv_obj_align(button, LV_ALIGN_BOTTOM_MID, 0, 0);

    lv_obj_t *button_label = lv_label_create(button);
    lv_label_set_text(button_label, "Config");
    lv_obj_center(button_label);

    lv_obj_add_event_cb(button, buttonEventCallback, LV_EVENT_CLICKED, this);
}

void MainGUI::createTopRightContainer()
{
    lv_obj_t *rightContainer = lv_obj_create(lv_scr_act());
    lv_obj_set_size(rightContainer, lv_pct(50), lv_pct(50));
    lv_obj_align(rightContainer, LV_ALIGN_TOP_RIGHT, 0, 0);

    lv_obj_t *title_label = lv_label_create(rightContainer);
    lv_label_set_text(title_label, "Profiles");
    lv_obj_set_style_text_font(title_label, &lv_font_montserrat_18, 0);
    lv_obj_align(title_label, LV_ALIGN_TOP_MID, 0, 10);

    lv_obj_t *logo = lv_label_create(rightContainer);
    lv_label_set_text(logo, LV_SYMBOL_DIRECTORY);
    lv_obj_set_style_text_font(logo, &lv_font_montserrat_24, 0);
    lv_obj_align(logo, LV_ALIGN_TOP_MID, 0, 30);

    lv_obj_t *button = lv_button_create(rightContainer);
    lv_obj_set_size(button, 80, 30);
    lv_obj_align(button, LV_ALIGN_BOTTOM_MID, 0, 0);

    lv_obj_t *button_label = lv_label_create(button);
    lv_label_set_text(button_label, "Load");
    lv_obj_center(button_label);

    lv_obj_add_event_cb(button, buttonEventCallback, LV_EVENT_CLICKED, this);
}

void MainGUI::createBottomContainer()
{
    lv_obj_t *rightContainer = lv_obj_create(lv_scr_act());
    lv_obj_set_size(rightContainer, lv_pct(100), lv_pct(50));
    lv_obj_align(rightContainer, LV_ALIGN_BOTTOM_LEFT, 0, 0);

    lv_obj_t *title_label = lv_label_create(rightContainer);
    lv_label_set_text(title_label, "Start");
    lv_obj_set_style_text_font(title_label, &lv_font_montserrat_18, 0);
    lv_obj_align(title_label, LV_ALIGN_TOP_MID, 0, 0);

    lv_obj_t *logo = lv_label_create(rightContainer);
    lv_label_set_text(logo, LV_SYMBOL_PLAY);
    lv_obj_set_style_text_font(logo, &lv_font_montserrat_24, 0);
    lv_obj_align(logo, LV_ALIGN_TOP_MID, 0, 25);

    lv_obj_t *button = lv_button_create(rightContainer);
    lv_obj_set_size(button, 120, 30);
    lv_obj_align(button, LV_ALIGN_BOTTOM_MID, 0, 0);

    lv_obj_t *button_label = lv_label_create(button);
    lv_label_set_text(button_label, "Start");
    lv_obj_center(button_label);

    lv_obj_add_event_cb(button, buttonEventCallback, LV_EVENT_CLICKED, this);
}

void MainGUI::buttonEventCallback(lv_event_t *e)
{
    lv_obj_t *button = (lv_obj_t *)lv_event_get_target(e);
    const char *button_label_text = lv_label_get_text(lv_obj_get_child(button, 0));

    MainGUI *gui = static_cast<MainGUI *>(lv_event_get_user_data(e));

    if (!gui)
    {

        return;
    }

    if (strcmp(button_label_text, "Config") == 0)
    {
        gui->showConfigScreen();
    }
    else if (strcmp(button_label_text, "Load") == 0)
    {
        gui->showLoadScreen();
    }
    else if (strcmp(button_label_text, "Start") == 0)
    {
        gui->showStartScreen();
    }
}

void MainGUI::buttonBackEventCallback(lv_event_t *e)
{
    MainGUI *gui = static_cast<MainGUI *>(lv_event_get_user_data(e));

    if (!gui)
    {

        return;
    }

    lv_obj_clean(lv_scr_act());

    gui->createGUI();
}

void MainGUI::showLoadScreen()
{
    lv_obj_clean(lv_scr_act());

    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Load");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *back_button = lv_button_create(lv_scr_act());
    lv_obj_set_size(back_button, 80, 40);
    lv_obj_align(back_button, LV_ALIGN_BOTTOM_RIGHT, -10, -10);

    lv_obj_t *back_label = lv_label_create(back_button);
    lv_label_set_text(back_label, "Back");
    lv_obj_center(back_label);

    lv_obj_add_event_cb(back_button, buttonBackEventCallback, LV_EVENT_CLICKED, this);
}

void MainGUI::showStartScreen()
{
    lv_obj_clean(lv_scr_act());

    lv_obj_t *title_label = lv_label_create(lv_scr_act());
    lv_label_set_text(title_label, "Solder Station Working");
    lv_obj_align(title_label, LV_ALIGN_TOP_MID, 0, 10);

    lv_obj_t *chart = lv_chart_create(lv_scr_act());
    lv_obj_set_size(chart, lv_pct(80), lv_pct(60));
    lv_obj_align(chart, LV_ALIGN_TOP_MID, 20, 40);

    lv_obj_set_style_border_color(chart, lv_color_black(), 0);
    lv_obj_set_style_border_width(chart, 2, 0);
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);

    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 320);

    lv_chart_set_point_count(chart, 100);

    ser1 = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);

    lv_obj_t *scale = lv_scale_create(lv_scr_act());
    lv_obj_set_size(scale, 15, lv_pct(50));
    lv_scale_set_mode(scale, LV_SCALE_MODE_VERTICAL_RIGHT);
    lv_scale_set_label_show(scale, true);

    lv_scale_set_range(scale, 0, 320);

    lv_scale_set_total_tick_count(scale, 5);

    lv_scale_set_major_tick_every(scale, 1);

    lv_obj_set_style_length(scale, 5, LV_PART_INDICATOR);
    lv_obj_align_to(scale, chart, LV_ALIGN_OUT_LEFT_MID, -20, 0);

    lv_obj_t *add_point_button = lv_btn_create(lv_scr_act());
    lv_obj_set_size(add_point_button, 100, 30);
    lv_obj_align(add_point_button, LV_ALIGN_BOTTOM_LEFT, 25, -10);

    lv_obj_t *add_point_label = lv_label_create(add_point_button);
    lv_label_set_text(add_point_label, "Add Point");
    lv_obj_center(add_point_label);

    lv_obj_add_event_cb(add_point_button, add_point_event_handler, LV_EVENT_CLICKED, chart);

    lv_obj_t *back_button = lv_btn_create(lv_scr_act());
    lv_obj_set_size(back_button, 60, 30);
    lv_obj_align(back_button, LV_ALIGN_BOTTOM_RIGHT, -25, -10);

    lv_obj_t *back_label = lv_label_create(back_button);
    lv_label_set_text(back_label, "Back");
    lv_obj_center(back_label);

    lv_obj_add_event_cb(back_button, buttonBackEventCallback, LV_EVENT_CLICKED, this);
}

void MainGUI::add_point_event_handler(lv_event_t *e)
{
    lv_obj_t *chart = (lv_obj_t *)lv_event_get_user_data(e);

    if (ser1 == nullptr)
        return;

    int value = point_index * 10;
    if (value > 320)
    {
        value = 320;
    }
    lv_chart_set_next_value(chart, ser1, value);

    point_index++;
    if (point_index >= 100)
    {
        point_index = 0;
    }
}

void MainGUI::showConfigScreen()
{
    lv_obj_clean(lv_scr_act());

    lv_obj_t *title_label = lv_label_create(lv_scr_act());
    lv_label_set_text(title_label, "Configuration");
    lv_obj_align(title_label, LV_ALIGN_TOP_MID, 0, 10);

    lv_obj_t *preheat_label = lv_label_create(lv_scr_act());
    lv_label_set_text(preheat_label, "Preheat Temp");
    lv_obj_align(preheat_label, LV_ALIGN_TOP_LEFT, 10, 50);

    lv_obj_t *preheat_temp_area = lv_textarea_create(lv_scr_act());
    lv_obj_set_size(preheat_temp_area, 100, 30);
    lv_obj_align(preheat_temp_area, LV_ALIGN_TOP_LEFT, 120, 50);
    lv_obj_add_event_cb(preheat_temp_area, textAreaEventCallback, LV_EVENT_FOCUSED, nullptr);

    lv_obj_t *preheat_time_label = lv_label_create(lv_scr_act());
    lv_label_set_text(preheat_time_label, "Time");
    lv_obj_align(preheat_time_label, LV_ALIGN_TOP_LEFT, 10, 90);

    lv_obj_t *preheat_time_area = lv_textarea_create(lv_scr_act());
    lv_obj_set_size(preheat_time_area, 100, 30);
    lv_obj_align(preheat_time_area, LV_ALIGN_TOP_LEFT, 120, 90);
    lv_obj_add_event_cb(preheat_time_area, textAreaEventCallback, LV_EVENT_FOCUSED, nullptr);

    lv_obj_t *solder_temp_label = lv_label_create(lv_scr_act());
    lv_label_set_text(solder_temp_label, "Solder Temp");
    lv_obj_align(solder_temp_label, LV_ALIGN_TOP_LEFT, 10, 130);

    lv_obj_t *solder_temp_area = lv_textarea_create(lv_scr_act());
    lv_obj_set_size(solder_temp_area, 100, 30);
    lv_obj_align(solder_temp_area, LV_ALIGN_TOP_LEFT, 120, 130);
    lv_obj_add_event_cb(solder_temp_area, textAreaEventCallback, LV_EVENT_FOCUSED, nullptr);

    lv_obj_t *solder_time_label = lv_label_create(lv_scr_act());
    lv_label_set_text(solder_time_label, "Time");
    lv_obj_align(solder_time_label, LV_ALIGN_TOP_LEFT, 10, 170);

    lv_obj_t *solder_time_area = lv_textarea_create(lv_scr_act());
    lv_obj_set_size(solder_time_area, 100, 30);
    lv_obj_align(solder_time_area, LV_ALIGN_TOP_LEFT, 120, 170);
    lv_obj_add_event_cb(solder_time_area, textAreaEventCallback, LV_EVENT_FOCUSED, nullptr);

    lv_obj_t *set_button = lv_button_create(lv_scr_act());
    lv_obj_set_size(set_button, 80, 40);
    lv_obj_align(set_button, LV_ALIGN_TOP_RIGHT, -10, 10);

    lv_obj_t *set_button_label = lv_label_create(set_button);
    lv_label_set_text(set_button_label, "Set");
    lv_obj_center(set_button_label);

    lv_obj_add_event_cb(set_button, setButtonEventCallback, LV_EVENT_CLICKED, nullptr);

    lv_obj_t *display_label = lv_label_create(lv_scr_act());
    lv_obj_align(display_label, LV_ALIGN_BOTTOM_MID, 0, -60);
    lv_label_set_text(display_label, "");

    lv_obj_t *back_button = lv_button_create(lv_scr_act());
    lv_obj_set_size(back_button, 80, 40);
    lv_obj_align(back_button, LV_ALIGN_BOTTOM_RIGHT, -10, -10);

    lv_obj_t *back_button_label = lv_label_create(back_button);
    lv_label_set_text(back_button_label, "Back");
    lv_obj_center(back_button_label);

    lv_obj_add_event_cb(back_button, buttonBackEventCallback, LV_EVENT_CLICKED, this);
}

void MainGUI::keyboardEventCallback(lv_event_t *e)
{
    lv_obj_t *keyboard = (lv_obj_t *)lv_event_get_target(e);

    if (keyboard != nullptr)
    {
        lv_obj_del(keyboard);
    }
}

void MainGUI::textAreaEventCallback(lv_event_t *e)
{
    lv_obj_t *ta = (lv_obj_t *)lv_event_get_target(e);

    if (lv_event_get_code(e) == LV_EVENT_FOCUSED)
    {
        lv_obj_t *keyboard = lv_keyboard_create(lv_scr_act());
        lv_keyboard_set_textarea(keyboard, ta);

        lv_keyboard_set_mode(keyboard, LV_KEYBOARD_MODE_NUMBER);

        lv_obj_add_event_cb(keyboard, keyboardEventCallback, LV_EVENT_READY, nullptr);
    }
}

void MainGUI::setButtonEventCallback(lv_event_t *e)
{

    lv_obj_t *screen = lv_scr_act();

    lv_obj_t *preheat_temp_area = lv_obj_get_child(screen, 2);
    lv_obj_t *preheat_time_area = lv_obj_get_child(screen, 4);
    lv_obj_t *solder_temp_area = lv_obj_get_child(screen, 6);
    lv_obj_t *solder_time_area = lv_obj_get_child(screen, 8);

    const char *preheat_temp = lv_textarea_get_text(preheat_temp_area);
    const char *preheat_time = lv_textarea_get_text(preheat_time_area);
    const char *solder_temp = lv_textarea_get_text(solder_temp_area);
    const char *solder_time = lv_textarea_get_text(solder_time_area);


    Serial.println("Valores de los campos de texto:");
    Serial.print("Preheat Temp: ");
    Serial.println(preheat_temp);
    Serial.print("Preheat Time: ");
    Serial.println(preheat_time);
    Serial.print("Solder Temp: ");
    Serial.println(solder_temp);
    Serial.print("Solder Time: ");
    Serial.println(solder_time);
}
