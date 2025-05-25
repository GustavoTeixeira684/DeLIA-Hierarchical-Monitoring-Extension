#include "Settings.h"


Settings::Settings(int size){
    this->size = size;
}

void Settings::SerializeSettings(std::string ft_path){
    FILE *fp;
    // The complete path of data that will be saved
    std::string path = ft_path + settings_filename;
    fp = fopen(path.c_str(), "wb");
    
    // Saving jut the size
    fwrite(&this->size, sizeof(int), 1, fp);
    fclose(fp);
}

bool Settings::CanRecover(std::string ft_path){

    std::string path = ft_path + settings_filename;
    FILE *fp;
    fp = fopen(path.c_str(), "rb");
    // Try to open the file
    if( fp == NULL) {
        #ifdef VERBOSE
        std::cerr << " File " << path << " don't exist " << std::endl;
        #endif
        return false;
    }

    int size_saved;
    // Try to read the file and save in other variable size
    size_t fread_result =  fread(&size_saved, sizeof(int), 1, fp);
    if (fread_result == 0) {
        std::cerr << "Error while reading Settings " << std::endl;
        fclose(fp);
        return false;
    }

    // Checks if the size saved is the same of the current execution
    if (size_saved != size) {
        #ifdef VERBOSE
        std::cerr << " Different configuration "<< std::endl;
        #endif
        return false;
    }    

    return true;
}