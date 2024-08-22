#ifndef DEVICE_H
#define DEVICE_H

#include "UserSettings.h"
#include <lvgl.h>
#include <EEPROM.h>
#include "max6675.h"  // Include the MAX6675 library

class Device
{
private:
    UserSettings settings;
    UserSettings data;
    lv_obj_t *chart;
    lv_chart_series_t *ser1;
    bool start;

    // MAX6675 Thermocouple pins
    int thermoDO;
    int thermoCS;
    int thermoCLK;
    MAX6675 thermocouple;

public:
    // Constructor vacío
    Device();

    // Función PID (sin implementación por ahora)
    void PID();

    void setChart(lv_obj_t *c, lv_chart_series_t *s);

    void addDatachar();

    void setStart(bool s);

    // Getter por referencia
    UserSettings &getSettings();

    // Método para guardar settings en EEPROM
    void saveSettingsToEEPROM(int startAddress);

    void deleteSettings(int startAddress);

    // Método para cargar settings desde EEPROM
    UserSettings &loadSettingsFromEEPROM(int startAddress);

    // Método para ver las primeras 100 muestras de EEPROM
    void printFirst100EEPROM();

    // Método para borrar las primeras 100 muestras de EEPROM
    void clearFirst100EEPROM();

    // Método para inicializar EEPROM
    void begin();

    // Método para leer la temperatura del termopar
    float readTemperature();
};

#endif // DEVICE_H
