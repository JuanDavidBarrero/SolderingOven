#include "Device.h"

Device::Device()
{
}

void Device::PID()
{
}

void Device::begin() {
    EEPROM.begin(1024);
}

UserSettings &Device::getSettings()
{
    return settings;
}

void Device::saveSettingsToEEPROM(int startAddress)
{
    int size = sizeof(UserSettings);
    if (startAddress + size > EEPROM.length())
    {
        Serial.println("Error: EEPROM overflow.");
        return;
    }

    byte *ptr = (byte *)&settings;
    for (int i = 0; i < size; ++i)
    {
        EEPROM.write(startAddress + i, ptr[i]);
        delay(50);
    }
    EEPROM.commit();
}

void Device::deleteSettings(int startAddress)
{
    int size = sizeof(UserSettings);
    if (startAddress + size > EEPROM.length())
    {
        Serial.println("Error: EEPROM overflow.");
        return;
    }

    // Reemplaza los datos con 0
    for (int i = 0; i < size; ++i)
    {
        EEPROM.write(startAddress + i, 0);
        delay(50);
    }
    EEPROM.commit();
}


UserSettings& Device::loadSettingsFromEEPROM(int startAddress)
{
    int size = sizeof(UserSettings);
    if (startAddress + size > EEPROM.length())
    {
        Serial.println("Error: EEPROM read overflow.");
        return settings;  // Devuelve una referencia a settings, aunque no esté correctamente cargada
    }

    // Lee directamente desde EEPROM a settings usando memcpy
    EEPROM.get(startAddress, data);

    return data;  // Devuelve la referencia a settings cargado desde EEPROM
}

void Device::printFirst100EEPROM()
{
    Serial.println("Primeros 100 bytes de EEPROM (10x10):");
    for (int i = 0; i < 100; ++i)
    {
        byte value = EEPROM.read(i);

        Serial.print(value, DEC);

        Serial.print(" ");

        if ((i + 1) % 10 == 0)
        {
            Serial.println();
        }
    }
}

void Device::clearFirst100EEPROM()
{
    Serial.println("Borrando los primeros 100 bytes de EEPROM...");
    for (int i = 0; i < 100; ++i)
    {
        EEPROM.write(i, 0);
    }
    EEPROM.commit();
    Serial.println("Primera 100 bytes borrados.");
}
