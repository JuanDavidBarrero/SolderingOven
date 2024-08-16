#ifndef DEVICE_H
#define DEVICE_H

#include "UserSettings.h"

class Device {
private:
    UserSettings settings;

public:
    // Constructor vacío
    Device();

    // Función PID (sin implementación por ahora)
    void PID();

    // Getter por referencia
    UserSettings& getSettings();
};

#endif // DEVICE_H
