#ifndef IDATASETTINGS_H
#define IDATASETTINGS_H
/// @cond
#include <iostream>
/// @endcond

/**
 * @file IDataSettings.h
 * @author Carla Santana (carla.ecomp@gmail.com)
 * @brief Interface to define the class that have the settings of the application
 * @version 1.0
 * @date 2022-10-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
class IDataSettings
{
    private:
        /**
         * @brief Name of the file that it will have 
         * the settings of the class
         * 
         */
        std::string settings_filename;  
    public:
        /**
         * @brief Function to save the settings of the application
         * 
         * @param ft_path the path of the folder where the data should be saved 
         */
        virtual void SerializeSettings(std::string ft_path) =0;
        
        /**
         * @brief Function that checks if the last checkpointing has 
         * the same configuration of the current execution
         * 
         * @param ft_path the path of the folder where the data was saved 
         * @return true. If the last settings are the same of 
         * the current execution 
         * @return false. If the last settings are not the same of 
         * the current execution 
         */
        virtual bool CanRecover(std::string ft_path) = 0;
        virtual ~IDataSettings(){};
};
#endif