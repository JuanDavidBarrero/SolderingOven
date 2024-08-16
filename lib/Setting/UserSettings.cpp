#include "UserSettings.h"

// Constructor por defecto
UserSettings::UserSettings() 
    : preheatTemp(0), time_preheat(0), solderTemp(0), time_solder(0) {}

// Getters
uint16_t UserSettings::getPreheatTemp() const {
    return preheatTemp;
}

uint16_t UserSettings::getTimePreheat() const {
    return time_preheat;
}

uint16_t UserSettings::getSolderTemp() const {
    return solderTemp;
}

uint16_t UserSettings::getTimeSolder() const {
    return time_solder;
}

// Setters
void UserSettings::setPreheatTemp(uint16_t temp) {
    preheatTemp = temp;
}

void UserSettings::setTimePreheat(uint16_t time) {
    time_preheat = time;
}

void UserSettings::setSolderTemp(uint16_t temp) {
    solderTemp = temp;
}

void UserSettings::setTimeSolder(uint16_t time) {
    time_solder = time;
}
