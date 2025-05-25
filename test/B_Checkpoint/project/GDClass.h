/**
 * @file GDClass.h
 * @author Carla Santana (carla.ecomp@gmail.com)
 * @brief Indicating that GDClass implements IDataGlobal
 * @version 1.0
 * @date 2022-10-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <fstream>

class GDClass {
    
    public:
        // Variable from the own class
        int *data_int; // important data to be saved
        double *data_double; // important data to be saved
        char *data_char; // important data to be saved
        float *data_float; // important data to be saved
        int size; // size of data
        int last_i;
    
    public:
        // Functions from the own class
        GDClass(int size);
        ~GDClass();
        void SaveFinalData(char* filename);
        void add(int value);
};