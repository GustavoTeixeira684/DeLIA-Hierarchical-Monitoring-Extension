#ifndef SETTINGS_H
#define SETTINGS_H

// including the IDataSettings
#include "IDataSettings.h"

// Indicating that Settings implements IDataSettings
class Settings : public IDataSettings {
    private:
        int size;
        // Initializing the variable from IDataSettings
        std::string settings_filename = "/settings.bin";  
    public:
        Settings(int size);
        ~Settings(){};
        // Declaring the functions from IDataSettings
        void SerializeSettings(std::string ft_path);
        bool CanRecover(std::string ft_path);
};
#endif