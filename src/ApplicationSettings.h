#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include "../include/IDataSettings.h"
#include <fstream>

// Indicating that Settings implements IDataSettings
/**
 * @brief Generic class to represent the settings of an application.
 * If the application does not pass IDataSettings, this class is used
 * 
 */
class ApplicationSettings : public IDataSettings {
    private:
        int size;
        // Initializing the variable from IDataSettings
        std::string settings_filename = "/settings.bin";  
        std::string configfile;  
    public:
        ApplicationSettings(std::string configfile);
        ~ApplicationSettings(){};
        // Declaring the functions from IDataSettings
        void SerializeSettings(std::string ft_path);
        bool CanRecover(std::string ft_path);
};
#endif