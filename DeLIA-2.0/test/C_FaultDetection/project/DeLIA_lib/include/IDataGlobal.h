#ifndef IDATAGLOBAL_H
#define IDATAGLOBAL_H
/// @cond
#include <iostream>
/// @endcond
/**
 * @file IDataGlobal.h
 * @author Carla Santana (carla.ecomp@gmail.com)
 * @brief Interface to define the class that have the global data
 * @version 1.0
 * @date 2022-10-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

class IDataGlobal
{
    private:
        /**
         * @brief Name of the file that it will have 
         * the global data of the classsaved
         * 
         */
        std::string global_data_filename;  
    public:
        /**
         * @brief Function to save the important global data
         * 
         * @param ft_path the path of the folder where the data should be saved 
         */
        virtual void SerializeGlobal(std::string ft_path) =0;

        /**
         * @brief Function to read the important global data
         * 
         * @param ft_path the path of the folder where the data should be saved
         * @return true. If the data were read with sucess
         * @return false. If the data were not read with sucess 
         */
        virtual bool DeserializeGlobal(std::string ft_path) =0;
        
        /**
         * @brief Function to return the name of the class
         * 
         * @return std::string const 
         */
        virtual std::string const getName() =0;
        
        // Function to test if the data are being saved and written correctly. 
        #ifdef TEST
        virtual bool TestRecoverGlobal(std::string ft_path)=0;
        #endif
        /**
         * @brief Destroy the IDataGlobal object
         * 
         */
        virtual ~IDataGlobal(){};
};
#endif