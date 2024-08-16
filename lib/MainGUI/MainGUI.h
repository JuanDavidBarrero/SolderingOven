#ifndef MAIN_GUI_H
#define MAIN_GUI_H

#include "Arduino.h"
#include <lvgl.h>
#include "Settings.h"
#include "Device.h"

class MainGUI
{
public:
    MainGUI(Device& device);

    // Función para crear la interfaz principal
    void createGUI();

    // Funciones para mostrar las pantallas específicas
    void showConfigScreen();
    void showLoadScreen();
    void showStartScreen();

private:
    static int point_index;         // Variable estática para llevar el seguimiento del índice del punto
    static lv_chart_series_t *ser1; // Variable estática para la serie del gráfico
    static Device *devicePtr;       // Puntero estático al objeto Device
    // Funciones auxiliares para crear partes de la interfaz
    void createTopLeftContainer();
    void createTopRightContainer();
    void createBottomContainer();

    // Callback para los eventos de los botones
    static void buttonEventCallback(lv_event_t *e);
    static void buttonBackEventCallback(lv_event_t *e);
    static void textAreaEventCallback(lv_event_t *e);
    static void setButtonEventCallback(lv_event_t *e);
    static void keyboardEventCallback(lv_event_t *e);
    static void buttonSaveEventCallback(lv_event_t *e);
    static void buttonDeleteEventCallback(lv_event_t *e);
    static void buttonPlayEventCallback(lv_event_t *e);
};

#endif // MAIN_GUI_H
