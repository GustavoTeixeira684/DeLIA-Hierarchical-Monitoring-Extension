/**
 * @file GDClass.cpp
 * @author Carla Santana (carla.ecomp@gmail.com)
 * @brief Indicating that GDClass implements IDataGlobal
 * @version 1.0
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "GDClass.h"

GDClass::GDClass(int size) {

    this->last_i =0;
    this->size = size;
    data_double = new double[size];
    data_int = new int[size];
    data_float = new float[size];
    data_char = new char[6];
    data_char[0]='i';
    data_char[1]='t';
    data_char[2]=' ';
    data_char[3]=' ';
    data_char[4]=' ';
    data_char[5]=' ';

    for (int i = 0; i < size; i++){
        data_double[i] = 1;
        data_int[i] = 1;
        data_float[i] = 1;
    }
}
void GDClass::add(int value) {
    last_i = value;
    for (int i = 0; i < size; i++){
        data_double[i] = i*value + data_double[i] +0.5;
        data_int[i] = i*value + data_int[i];
        data_float[i] = i*value + data_int[i]+ 0.25;
    }
    std::sprintf(data_char,"it %d", value);
}

void GDClass::SaveFinalData(char* filename){

    std::ofstream ofstream_ob(filename, std::ios::out);
        
    for (int i = 0; i < size; i++){
        ofstream_ob << data_int[i] << ", ";
    } 
    ofstream_ob <<"\n";
    
    for (int i = 0; i < size; i++){
        ofstream_ob << data_float[i] << ", ";
    } 
    ofstream_ob <<"\n";
    
    for (int i = 0; i < size; i++){
        ofstream_ob << data_double[i] << ", ";
    } 

    ofstream_ob <<"\n";
    
    ofstream_ob << data_char << "\n";
    ofstream_ob.close();
}

GDClass::~GDClass(){
    delete [] data_double;
    delete [] data_int;
    delete [] data_float;
    delete [] data_char;
}