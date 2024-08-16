#ifndef UserSETTINGS_H
#define UserSETTINGS_H

#include <cstdint>

class UserSettings {
private:
    uint16_t preheatTemp;
    uint16_t time_preheat;
    uint16_t solderTemp;
    uint16_t time_solder;

public:
    // Constructor por defecto
    UserSettings();

    // Getters
    uint16_t getPreheatTemp() const;
    uint16_t getTimePreheat() const;
    uint16_t getSolderTemp() const;
    uint16_t getTimeSolder() const;

    // Setters
    void setPreheatTemp(uint16_t temp);
    void setTimePreheat(uint16_t time);
    void setSolderTemp(uint16_t temp);
    void setTimeSolder(uint16_t time);
};

#endif // UserSETTINGS_H
