#include "MainGUI.h"

int MainGUI::point_index = 0;
lv_chart_series_t *MainGUI::ser1 = nullptr;
Device *MainGUI::devicePtr = nullptr;

MainGUI::MainGUI(Device &device)
{
    devicePtr = &device;
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

    devicePtr->setStart(false);
    lv_obj_clean(lv_scr_act());

    gui->createGUI();
}

void MainGUI::showLoadScreen()
{

    lv_obj_clean(lv_scr_act());

    int rowHeight = 65;

    for (int i = 0; i < 3; ++i)
    {

        UserSettings &settings = devicePtr->loadSettingsFromEEPROM(i * sizeof(UserSettings));

        lv_obj_t *row = lv_obj_create(lv_scr_act());
        lv_obj_set_size(row, lv_pct(100), rowHeight);
        lv_obj_align(row, LV_ALIGN_TOP_MID, 0, i * (rowHeight));

        lv_obj_set_user_data(row, (void *)(intptr_t)i);

        lv_obj_t *dataLabel = lv_label_create(row);
        char buf[256];
        sprintf(buf, "Preheat: %d°C Time: %d min \r\n Heat: %d°C Time: %d min",
                settings.getPreheatTemp(), settings.getTimePreheat(),
                settings.getSolderTemp(), settings.getTimeSolder());
        lv_label_set_text(dataLabel, buf);
        lv_obj_set_style_text_font(dataLabel, &lv_font_montserrat_12, 0);
        lv_obj_align(dataLabel, LV_ALIGN_LEFT_MID, 0, 0);

        lv_obj_t *saveButton = lv_button_create(row);
        lv_obj_set_size(saveButton, 35, 35);
        lv_obj_align(saveButton, LV_ALIGN_RIGHT_MID, -90, 0);
        lv_obj_set_style_bg_color(saveButton, lv_color_hex(0x0000FF), 0);

        lv_obj_t *saveIcon = lv_label_create(saveButton);
        lv_label_set_text(saveIcon, LV_SYMBOL_SAVE);
        lv_obj_set_style_text_font(saveIcon, &lv_font_montserrat_14, 0);
        lv_obj_center(saveIcon);
        lv_obj_add_event_cb(saveButton, buttonSaveEventCallback, LV_EVENT_CLICKED, this);

        lv_obj_t *deleteButton = lv_button_create(row);
        lv_obj_set_size(deleteButton, 35, 35);
        lv_obj_align(deleteButton, LV_ALIGN_RIGHT_MID, -50, 0);
        lv_obj_set_style_bg_color(deleteButton, lv_color_hex(0xFF0000), 0);

        lv_obj_t *deleteIcon = lv_label_create(deleteButton);
        lv_label_set_text(deleteIcon, LV_SYMBOL_TRASH);
        lv_obj_set_style_text_font(deleteIcon, &lv_font_montserrat_14, 0);
        lv_obj_center(deleteIcon);
        lv_obj_add_event_cb(deleteButton, buttonDeleteEventCallback, LV_EVENT_CLICKED, this);

        lv_obj_t *playButton = lv_button_create(row);
        lv_obj_set_size(playButton, 35, 35);
        lv_obj_align(playButton, LV_ALIGN_RIGHT_MID, -10, 0);
        lv_obj_set_style_bg_color(playButton, lv_color_hex(0x00FF00), 0);

        lv_obj_t *playIcon = lv_label_create(playButton);
        lv_label_set_text(playIcon, LV_SYMBOL_PLAY);
        lv_obj_set_style_text_font(playIcon, &lv_font_montserrat_14, 0);
        lv_obj_center(playIcon);
        lv_obj_add_event_cb(playButton, buttonPlayEventCallback, LV_EVENT_CLICKED, this);
    }

    lv_obj_t *backButton = lv_button_create(lv_scr_act());
    lv_obj_set_size(backButton, 60, 30);
    lv_obj_align(backButton, LV_ALIGN_BOTTOM_RIGHT, -20, -10);

    lv_obj_t *backButtonLabel = lv_label_create(backButton);
    lv_label_set_text(backButtonLabel, LV_SYMBOL_LEFT);
    lv_obj_set_style_text_font(backButtonLabel, &lv_font_montserrat_14, 0);
    lv_obj_center(backButtonLabel);

    lv_obj_add_event_cb(backButton, buttonBackEventCallback, LV_EVENT_CLICKED, this);
}

void MainGUI::showStartScreen()
{
    lv_obj_clean(lv_scr_act());
    UserSettings &settings = devicePtr->getSettings();

    // Título
    lv_obj_t *title_label = lv_label_create(lv_scr_act());
    lv_label_set_text(title_label, "Solder Station Working");
    lv_obj_align(title_label, LV_ALIGN_TOP_MID, 0, 10);

    // Gráfico
    lv_obj_t *chart = lv_chart_create(lv_scr_act());
    lv_obj_set_size(chart, lv_pct(80), lv_pct(60));
    lv_obj_align(chart, LV_ALIGN_TOP_MID, 20, 40);

    lv_obj_set_style_border_color(chart, lv_color_black(), 0);
    lv_obj_set_style_border_width(chart, 2, 0);
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    lv_obj_set_style_size(chart, 0, 0, LV_PART_INDICATOR);

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

    // Etiqueta para mostrar los datos de UserSettings
    lv_obj_t *data_label = lv_label_create(lv_scr_act());
    char buf[256];
    sprintf(buf,
            "Temp pre: %d°C    Temp sol: %d°C\n"
            "Time:      %d min      Time:      %d min",
            settings.getPreheatTemp(), settings.getSolderTemp(),
            settings.getTimePreheat(), settings.getTimeSolder());
    lv_label_set_text(data_label, buf);
    lv_obj_set_style_text_font(data_label, &lv_font_montserrat_12, 0); // Fuente más pequeña
    lv_obj_align(data_label, LV_ALIGN_BOTTOM_LEFT, 10, -10);           // Ajusta la posición entre los botones

    // Botón "Back"
    lv_obj_t *back_button = lv_btn_create(lv_scr_act());
    lv_obj_set_size(back_button, 60, 30);
    lv_obj_align(back_button, LV_ALIGN_BOTTOM_RIGHT, -15, -10);

    lv_obj_t *back_label = lv_label_create(back_button);
    lv_label_set_text(back_label, "Back");
    lv_obj_center(back_label);

    devicePtr->setChart(chart, ser1);

    lv_obj_add_event_cb(back_button, buttonBackEventCallback, LV_EVENT_CLICKED, this);
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

    UserSettings &settings = devicePtr->getSettings();

    settings.setPreheatTemp(atoi(preheat_temp));
    settings.setTimePreheat(atoi(preheat_time));
    settings.setSolderTemp(atoi(solder_temp));
    settings.setTimeSolder(atoi(solder_time));
}

void MainGUI::buttonSaveEventCallback(lv_event_t *e)
{

    lv_obj_t *obj = (lv_obj_t *)lv_event_get_target(e);

    lv_obj_t *row = lv_obj_get_parent(obj); 
    int rowIndex = (int)(intptr_t)lv_obj_get_user_data(row);

    devicePtr->saveSettingsToEEPROM(rowIndex * sizeof(UserSettings));

    Serial.print("Save icon clicked on row ");
    Serial.println(rowIndex);
}

void MainGUI::buttonDeleteEventCallback(lv_event_t *e)
{

    lv_obj_t *obj = (lv_obj_t *)lv_event_get_target(e);

    lv_obj_t *row = lv_obj_get_parent(obj);
    int rowIndex = (int)(intptr_t)lv_obj_get_user_data(row);

    devicePtr->deleteSettings(rowIndex * sizeof(UserSettings));

    Serial.print("Delete icon clicked on row ");
    Serial.println(rowIndex);
}

void MainGUI::buttonPlayEventCallback(lv_event_t *e)
{

    lv_obj_t *obj = (lv_obj_t *)lv_event_get_target(e);

    lv_obj_t *row = lv_obj_get_parent(obj);
    int rowIndex = (int)(intptr_t)lv_obj_get_user_data(row);

    UserSettings &data = devicePtr->loadSettingsFromEEPROM(rowIndex * sizeof(UserSettings));

    UserSettings &settings = devicePtr->getSettings();
    settings.setPreheatTemp(data.getPreheatTemp());
    settings.setTimePreheat(data.getTimePreheat());
    settings.setSolderTemp(data.getSolderTemp());
    settings.setTimeSolder(data.getTimeSolder());

    Serial.print("\n\nCurrent Settings play button:\n");
    Serial.print("Preheat Temp: ");
    Serial.print(settings.getPreheatTemp());
    Serial.print("°C\nTime Preheat: ");
    Serial.print(settings.getTimePreheat());
    Serial.print(" s\nSolder Temp: ");
    Serial.print(settings.getSolderTemp());
    Serial.print("°C\nTime Solder: ");
    Serial.print(settings.getTimeSolder());
    Serial.println(" s");
}
