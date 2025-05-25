#include "ApplicationSettings.h"


ApplicationSettings::ApplicationSettings(std::string configfile){
    this->configfile = configfile;
}

void ApplicationSettings::SerializeSettings(std::string ft_path){
    std::string ftconfigfile = ft_path + settings_filename;
    std::ifstream src;
    std::ofstream dst;

    src.open(configfile, std::ios::in | std::ios::binary);
    dst.open(ftconfigfile, std::ios::out | std::ios::binary);
    dst << src.rdbuf();

    src.close();
    dst.close();
}

bool ApplicationSettings::CanRecover(std::string ft_path){

    std::ifstream file1, file2;
    std::string ftconfigfile = ft_path + settings_filename;
    
    file1.open (ftconfigfile, std::ios::in| std::ios::binary);
    file2.open (configfile, std::ios::in| std::ios::binary);
    // std::ifstream file2(configpath, std::ifstream::binary|std::ifstream::ate);

    if (file1.fail() || file2.fail()) {
        return false; //file problem
    }

    if (file1.tellg() != file2.tellg()) {
        return false; //size mismatch
    }

    //seek back to beginning and use std::equal to compare contents
    file1.seekg(0, std::ifstream::beg);
    file2.seekg(0, std::ifstream::beg);
    return std::equal(std::istreambuf_iterator<char>(file1.rdbuf()),
                        std::istreambuf_iterator<char>(),
                        std::istreambuf_iterator<char>(file2.rdbuf()));
}