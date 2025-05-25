#include "LDClass.h"

LDClass::LDClass(int size) {
    this->size = size;
    i_global=0;
    global_data = new int[size];
    for (int i = 0; i < size; i++) {
        global_data[i] = 0;
    }
    local_data = new int[size];
    
}

void LDClass::add(int value){
    
    if (!(DeLIA_CanRecoverLocalCheckpointing() && DeLIA_ReadLocalData())) {
        last_i_local = -1;
        for (int i = 0; i < size; i++) {
            local_data[i] = 0;
        }
    }
    
    int i = last_i_local +1;
    for (i; i < size; i++) {
        local_data[i] = local_data[i] + value;
        last_i_local = i;        
        DeLIA_SaveLocalData();
    }

    for (i; i < size; i++) {
        global_data[i] = 2*local_data[i];
    }
    // sleep(1);

}

void LDClass::SerializeGlobal(std::string ft_path) {
    FILE *fp;
    // The complete path of data that will be saved
    std::string path = ft_path + global_data_filename;
    fp = fopen(path.c_str(), "wb");
    fwrite(this->global_data, sizeof(int), this->size, fp);
    fwrite(&this->i_global, sizeof(int), 1, fp);
    fclose(fp);
}

bool LDClass::DeserializeGlobal(std::string ft_path) {
    std::string path = ft_path + global_data_filename;
    FILE *fp;
    // Try to open the file
    fp = fopen(path.c_str(), "rb");
    if( fp == NULL) {
        std::cerr << " File " << path << " don't exist " << std::endl;
        return false;
    }
    // Try to read the file and save in the variable data
    size_t fread_result =  fread(this->global_data, sizeof(int), this->size, fp);
    if (fread_result == 0) {
        std::cerr << "Error while reading " << path << " => variable GLOBAL DATA " << std::endl;
        fclose(fp);
        return false;
    }
    fread_result =  fread(&this->i_global, sizeof(int), 1, fp);
    if (fread_result == 0) {
        std::cerr << "Error while reading " << path << " => variable I GLOBAL " << std::endl;
        fclose(fp);
        return false;
    }
    fclose(fp);
    return true;
}

void LDClass::SerializeLocal(std::string ft_path) {
    FILE *fp;
    // The complete path of local data that will be saved
    std::string path = ft_path + local_data_filename;
    fp = fopen(path.c_str(), "wb");
    fwrite(this->local_data, sizeof(int), this->size, fp);
    fwrite(&last_i_local, sizeof(int), 1, fp);
    fclose(fp);
    #ifdef DEBUG
        std::cout << "SerializeLocal " << std::endl;
        std::cout << "------------------------------" << std::endl;
    #endif
}

bool LDClass::DeserializeLocal(std::string ft_path) {
    std::string path = ft_path + local_data_filename;
    FILE *fp;
    // Try to open the file
    fp = fopen(path.c_str(), "rb");
    if( fp == NULL) {
        std::cerr << " File " << path << " don't exist " << std::endl;
        return false;
    }
    // Try to read the file and save in the variable data
    size_t fread_result =  fread(this->local_data, sizeof(int), this->size, fp);
    if (fread_result == 0) {
        std::cerr << "Error while reading " << path << " => variable LOCAL DATA " << std::endl;
        fclose(fp);
        return false;
    }
    // Try to read the file and save in the variable data
    fread_result =  fread(&last_i_local, sizeof(int), 1, fp);
    if (fread_result == 0) {
        std::cerr << "Error while reading " << path << " => variable LAST I " << std::endl;
        fclose(fp);
        return false;
    }

    return true;
}

LDClass::~LDClass() {
    delete [] global_data;
    delete [] local_data;
}

#ifdef TEST
bool LDClass::TestRecoverGlobal(std::string ft_path) {

    // Make a copy of the current global_data
    int *data_copy;
    data_copy = new int[size];
    for (int i = 0; i < size; i++) {
        data_copy[i] = global_data[i];
    }

    int i_copy = i_global;
    // Serialize the global_data
    this->SerializeGlobal(ft_path);
    // Deserialize the global_data
    this->DeserializeGlobal(ft_path);

    // Check if the global_data is equal to data_copy
    for (int i = 0; i < size; i++) {
        if (data_copy[i] != global_data[i]){
        std::cerr << "DATA[" << i <<"] in " << this->getName() << " is not saved correctly" << std::endl;
        std::cerr << "data: " << global_data[i] << " data_copy: " << data_copy[i]<< std::endl;
        return false;
        }
    }
    if (i_copy != i_global) return false;
    return true;
}

bool LDClass::TestRecoverLocal(std::string ft_path) {

    // Make a copy of the current local_data
    int *data_copy;
    data_copy = new int[size];
    for (int i = 0; i < size; i++) {
        data_copy[i] = local_data[i];
    }

    int last_i_local_copy = last_i_local;
    // Serialize the local_data and last_i
    this->SerializeLocal(ft_path);
    // Deserialize the local_data and last_i
    this->DeserializeLocal(ft_path);

    // Check if the local_data is equal to data_copy
    for (int i = 0; i < size; i++) {
        if (data_copy[i] != local_data[i]){
        std::cerr << "LOCAL DATA[" << i <<"] in " << this->getName() << " is not saved correctly" << std::endl;
        std::cerr << "data: " << local_data[i] << " data_copy: " << data_copy[i]<< std::endl;
        return false;
        }
    }

    if (last_i_local != last_i_local_copy) return false;
    
    return true;
}
#endif