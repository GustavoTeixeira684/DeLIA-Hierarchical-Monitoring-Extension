#ifndef IDATALOCAL_H
#define IDATALOCAL_H
/// @cond
#include <iostream>
/// @endcond

/**
 * @file IDataLocal.h
 * @author Carla Santana (carla.ecomp@gmail.com)
 * @brief Interface to define the class that have the local data
 * @version 1.0
 * @date 2022-10-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
class IDataLocal
{
    private:
        /**
         * @brief Name of the file that it will have 
         * the local data of the class saved
         * 
         */
        std::string local_data_file_name;
    public:
        /**
         * @brief Function to save the important local data
         * 
         * @param ft_path the path of the folder where the data should be saved 
         */
        virtual void SerializeLocal(std::string ft_path) =0;
        virtual void SerializeTasks(std::string ft_path) =0;
        virtual bool DeserializeAllTaks(std::string ft_path) =0;
        
        /**
         * @brief Function to read the important local data
         * 
         * @param ft_path the path of the folder where the data should be saved
         * @return true. If the data were read with sucess
         * @return false. If the data were not read with sucess 
         */
        virtual bool DeserializeLocal(std::string ft_path) =0;

        
        // Function to test if the local data are being saved and written correctly.
        #ifdef TEST
        virtual bool TestRecoverLocal(std::string ft_path)=0;
        #endif
        virtual ~IDataLocal(){};
};
#endif