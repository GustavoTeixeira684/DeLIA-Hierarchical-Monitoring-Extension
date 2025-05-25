#include "Checkpointing.h"

Checkpointing* Checkpointing::instance = NULL;

Checkpointing* Checkpointing::getInstance(){
    if (!instance) {
        instance = new Checkpointing();
    }
    
    return instance;
}

void Checkpointing::releaseInstance() {
  if(nullptr != instance) {
    delete instance;
    instance = NULL;						
  }
}

/**
 * @brief Construct a new Checkpointing:: Checkpointing object
 * Checkpointing initialization:
 * Checks whether the last saved data matches the current configuration,
 * otherwise it saves the current data configuration
 *
 * @param ft_folder folder which the checkpoiting data will be saved
 * @param checkpointing_global_time interval in seconds that the checkpointing
 * will be done after the application called SaveGlobalData
 * @param checkpointing_local_time interval in seconds that the checkpointing
 * will be done after the application called SaveLocalData
 * @param checkpointing_global_iteration refers to the interval of iterations
 * that the checkpointing will be done the application called SaveGlobalData
 */
void Checkpointing::setParameters(std::string ft_folder,
                             int checkpointing_global_time, int checkpointing_local_time,
                             int checkpointing_local_time_diff,
                             int checkpointing_global_iteration,
                             bool checkpointing_local_recent,
                             std::string workload_scheduler, 
                             int workload_scheduler_leader) {
    this->fRead = true;
    this->fPathFolder = ft_folder;
    this->fCheckpointingGlobalTime = checkpointing_global_time;
    this->fCheckpointingLocalTime = checkpointing_local_time;
    this->fCheckpointingGlobalIteration = checkpointing_global_iteration;
    this->fCheckpointingLocalTimeDiff = checkpointing_local_time_diff;
    this->fCheckpointingLocalRecent = checkpointing_local_recent;
    this->fWorkloadScheduler = workload_scheduler;
    this->fWorkloadSchedulerLeader = workload_scheduler_leader;
    this->fTControl = 0;
    this->fTCurrent = 0;

    FILE *fp;
    std::string path = this->fPathFolder + "/DeLIA_Iteration_Localnode_" + 
                        std::to_string(Utils::getId())+".txt";
    fp=fopen(path.c_str(), "r");

    if(fp==NULL) {
        perror("Any local data was saved");
    } else {
        while(!feof(fp)) {
            int it;
            fscanf(fp, "%d", &it);
            fListLocalDataProcessed.insert(it);
        }
        fclose(fp);
    }
    time(&fLastGlobalCheckpointingTime);
    time(&fLastLocalCheckpointingTime);
}

/**
 * @brief Save the global data
 * The serialization of the data is split between the processes.
 * Examples with 4 IDataGlobal :
 * If 4 processes are running, each will call "SerializeGlobal" from each IDataGlobal.
 * If 2 processes are running, each will call "SerializeGlobal" from 2 IDataGlobal.
 * If there is only 1 process, it will call "SerializeGlobal" from all IDataGlobal.
 * If there are more than 4 processes, the first 4 will call
 * "SerializeGlobal" from each IDataGlobal.
 *
 * P.s.: The global data will be saved just after the
 * checkpointing_global_time and checkpointing_global_iteration
 *
 * @param id id of the process
 * @param comm_sz number of process
 */
void Checkpointing::SaveGlobalData() {
    fTCurrent++;
    int id = Utils::getId();
    int comm_sz = Utils::getComm_sz();
    if (fCheckpointingGlobalTime == -1 && fCheckpointingGlobalIteration <= 0) {
        #ifdef VERBOSE
        if (id == 0) {
            std::cout << "-----\t DeLIA Global Data is not actived \t-----" << std::endl;
        }
        #endif
        return;
    }

    time_t now;
    time(&now);
    double diff_time = difftime(now, fLastGlobalCheckpointingTime);
    

    if (diff_time < fCheckpointingGlobalTime ||
        (fCheckpointingGlobalIteration > 0 && fTCurrent % fCheckpointingGlobalIteration != 0)) {
        #ifdef DEBUG
        if (id == 0) {
            std::cout << "-----\t Global data will not be saved \t-----" << std::endl;
        }
        #endif
        return;
    }
    // fTControl = fTCurrent;
    #ifdef VERBOSE
    if (id == 0) {
        std::cout << "============================================" << std::endl;
        std::cout << "-----\t DeLIA::SaveGlobalData \t-----" << std::endl;
        std::cout << "-----\t Iteration: " << fTCurrent << "\t\t-----" << std::endl;
    }
    #endif

    int fDataSize = int(this->fIDataGlobal.size());
    if (fDataSize <= comm_sz) {
        if (Utils::getId() < fDataSize) {
            this->fIDataGlobal[id]->SerializeGlobal(this->fPathFolder + "/");
            #ifdef DEBUG
            std::cout << "-----\t Data from " << this->fIDataGlobal[id]->getName() << " saved by " << id << std::endl;
            #endif
        }
    } else {
        // Data global divided between the proceses
        int n = fDataSize / comm_sz;
        int limit;
        
        if (id+1 < comm_sz) {
            limit = n * (id + 1);
        } else {
            limit = fDataSize+1;
        }

        for (int i = n * id; i < limit; i++) {
            this->fIDataGlobal[i]->SerializeGlobal(this->fPathFolder+ "/");
            #ifdef DEBUG
            std::cout << "-------\t Data from " << this->fIDataGlobal[i]->getName() << " saved by " << id << "--------" << std::endl;
            #endif
        }
    }
    
    if (id == 0) {
        if (this->fDataGlobal.size() > 0) {
            FILE *fp;
            std::string path = this->fPathFolder+ "/DeLIA_GlobalData.bin";
            fp = fopen(path.c_str(), "wb");
            if( fp != NULL) {
                for (DeLIAData *Ddata : this->fDataGlobal){
                    size_t fread_result;
                    switch (Ddata->typeCode) {
                        case INT_CODE: {
                            fwrite(Ddata->data, sizeof(int), Ddata->sizeOfData, fp);
                            break;
                        }                
                        case DOUBLE_CODE: {
                            fwrite(Ddata->data, sizeof(double), Ddata->sizeOfData, fp);
                            break;
                        }                
                        case CHAR_CODE: {
                            fwrite(Ddata->data, sizeof(char), Ddata->sizeOfData, fp);
                            break;
                        }                
                        case FLOAT_CODE: {
                            fwrite(Ddata->data, sizeof(float), Ddata->sizeOfData, fp);
                            break;
                        }
                        case BOOL_CODE: {
                            fwrite(Ddata->data, sizeof(bool), Ddata->sizeOfData, fp);
                            break;
                        }                
                        default:
                            std::cerr << "ERROR NO TYPE" << std::endl;
                            break;
                    }             
                }
            }
            fclose(fp);
        }
       
        FILE *fp;
        std::string path = this->fPathFolder + "/DeLIA_gIteration.txt";
        fp = fopen(path.c_str(), "w"); 
        fprintf(fp, "%d", fTCurrent);
        fclose(fp);    
    }
    
    #ifdef VERBOSE
    if (id == 0) {
        std::cout << "============================================" << std::endl;
    }
    #endif

    time(&fLastGlobalCheckpointingTime);
    // fTCurrent++;
    fTControl = fTCurrent;
}

void Checkpointing::SaveLocalData() {
    
    time_t now;
    time(&now);
    double diff_time = difftime(now, fLastLocalCheckpointingTime);

    int id = Utils::getId();
    if (diff_time < fCheckpointingLocalTime || diff_time < fCheckpointingLocalTimeDiff) {
        return;
    }
    std::string path = this->fPathFolder + "/DeLIA_Local_" + "node_" + std::to_string(id)+ 
                            "_gIteration_" + std::to_string(this->fTCurrent) +"_";
    
    if (fCheckpointingLocalRecent){
        std::string path_remove = "rm -r " + this->fPathFolder + 
                                "/DeLIA_Local_"  + "node_" + std::to_string(id)+ 
                                "_gIteration_"+"* >>output.out 2>>erroutput.out";
        int result = system(path_remove.c_str());
        
        path_remove = "rm -r " + this->fPathFolder + 
                                "/DeLIA_LocalData_node_" + std::to_string(id)+ 
                                "_gIteration_"+"* >>output.out 2>>erroutput.out";
        result = system(path_remove.c_str());
                                        
    }
    
    for (IDataLocal *data : fIDataLocal) {        
        data->SerializeLocal(path);
    }

    if (this->fDataLocal.size() >0) {
        FILE *fp;
        std::string path = this->fPathFolder+ "/DeLIA_LocalData_node_" + std::to_string(id)+ 
                        "_gIteration_" + std::to_string(this->fTCurrent) +".bin";
        fp = fopen(path.c_str(), "wb");  

        if( fp != NULL) {
            for (DeLIAData *Ddata : this->fDataLocal){
                size_t fread_result;
                switch (Ddata->typeCode) {
                    case INT_CODE: {
                        fwrite(Ddata->data, sizeof(int), Ddata->sizeOfData, fp);
                        #ifdef TEST
                        FILE *fp2;
                        std::string path = this->fPathFolder + "/DeLIA_debug_n_" + 
                            "node_" + std::to_string(id)+".txt";
                        int * data = (int*)Ddata->data;
                        fp2 = fopen(path.c_str(), "w"); 
                        for (int i = 0; i < Ddata->sizeOfData; i++) {
                            fprintf(fp2, "%d ", data[i]);
                        }                            
                        fclose(fp2);
                        #endif
                        break;
                    }                
                    case DOUBLE_CODE: {
                        fwrite(Ddata->data, sizeof(double), Ddata->sizeOfData, fp);
                        break;
                    }                
                    case CHAR_CODE: {
                        fwrite(Ddata->data, sizeof(char), Ddata->sizeOfData, fp);
                        break;
                    }                
                    case FLOAT_CODE: {
                        fwrite(Ddata->data, sizeof(float), Ddata->sizeOfData, fp);
                        break;
                    }
                    case BOOL_CODE: {
                        fwrite(Ddata->data, sizeof(bool), Ddata->sizeOfData, fp);
                        break;
                    }                
                    default:
                        std::cerr << "NO TYPE" << std::endl;
                        break;
                }             
            }
            fclose(fp);
        }

        if (this->fDataLocalNeighbor.size() > 0) {
            int idn;
            if (id == 0){
                idn = Utils::getComm_sz() -1;
            } else {
                idn = id -1;
            }
            std::string path = this->fPathFolder+ "/DeLIA_LocalDataNeighbor_node_" 
                                    + std::to_string(idn) + "_gIteration_" 
                                    + std::to_string(this->fTCurrent) + ".bin";

            fp = fopen(path.c_str(), "wb"); 

            if( fp != NULL) {
                for (DeLIAData *Ddata : fDataLocalNeighbor){
                                        
                    size_t fread_result;
                    switch (Ddata->typeCode) {
                        case INT_CODE: {
                            fwrite(Ddata->data, sizeof(int), Ddata->sizeOfData, fp);
                            break;
                        }                
                        case DOUBLE_CODE: {
                            fwrite(Ddata->data, sizeof(double), Ddata->sizeOfData, fp);
                            break;
                        }                
                        case CHAR_CODE: {
                            fwrite(Ddata->data, sizeof(char), Ddata->sizeOfData, fp);
                            break;
                        }                
                        case FLOAT_CODE: {
                            fwrite(Ddata->data, sizeof(float), Ddata->sizeOfData, fp);
                            break;
                        }
                        case BOOL_CODE: {
                            fwrite(Ddata->data, sizeof(bool), Ddata->sizeOfData, fp);
                            break;
                        }                
                        default:
                            std::cerr << "NO TYPE" << std::endl;
                            break;
                    }             
                }
            }
            fclose(fp);
        }
        
    }

    #ifdef DEBUG
        std::cout << "============================================" << std::endl;
        std::cout << "-----\t DeLIA::SaveLocalData \t-----" << std::endl;
        std::cout << "-----\t ID: " << Utils::getId() << "\t\t\t-----" << std::endl;
        std::cout << "-----\t Iteration: " << fTCurrent << "\t\t-----" << std::endl;
    #endif

    if (fCheckpointingLocalRecent){
        FILE *fp;
        std::string path = this->fPathFolder + "/DeLIA_Iteration_Local" + 
                            "node_" + std::to_string(id)+".txt";
        fp = fopen(path.c_str(), "w"); 
        fprintf(fp, "%d", fTCurrent);
        fclose(fp);
    } else {
        FILE *fp;
        std::string path = this->fPathFolder + "/DeLIA_Iteration_Local" + 
                            "node_" + std::to_string(id)+".txt";
        fp = fopen(path.c_str(), "a");        
        fprintf(fp, "%d", fTCurrent);
        fclose(fp);
    }

    time(&fLastLocalCheckpointingTime);
    if (fWorkloadScheduler != "DS") {
        SaveTasks();
    }    
}


void Checkpointing::SaveTasks(){
    int id = Utils::getId();

    std::string path = this->fPathFolder + "/DeLIA_Files_LocalL_gIteration_" + 
                                            std::to_string(this->fTCurrent) 
                                            +"_Tasks_"+ "node_";
    
    for (IDataLocal *data : fIDataLocal) {        
        data->SerializeTasks(path);
    }

}

bool Checkpointing::ReadAllTaks(){
    std::vector<IDataLocal *>::iterator it;
    int comm_sz = Utils::getComm_sz();
    for (IDataLocal *data : fIDataLocal) {
        std::string path = this->fPathFolder + "/DeLIA_Files_LocalL_gIteration_" + std::to_string(this->fTCurrent) +"_Tasks_"
                                            + "node_";

        if (!data->DeserializeAllTaks(path)) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Read the global data,
 * all processes will read the global data from the last execution
 *
 * @return true If all data were read ok.
 * @return false If all data were not read ok.
 */
bool Checkpointing::ReadGlobalData() {
    
    int id = Utils::getId();
    std::vector<IDataGlobal *>::iterator it;

    for (IDataGlobal *data : this->fIDataGlobal) {
        #ifdef DEBUG
        std::cout << "Reading the data from " << data->getName() << std::endl;
        std::cout << "------------------------------" << std::endl;
        #endif
        if (!data->DeserializeGlobal(this->fPathFolder+ "/")) {
            std::cerr << "DATA WAS NOT SUCCESSFULLY READ IN " << id << std::endl;
            fRead = false;
            return false;
            break;
        }
    }
  
    FILE *fp;
    if (this->fDataGlobal.size() > 0) {
        std::string path = this->fPathFolder+ "/DeLIA_GlobalData.bin";
        std::cerr << "this->fDataGlobal.size()" << this->fDataGlobal.size() << std::endl;
        std::cerr << "this->fDataGlobal.max_size()" << this->fDataGlobal.max_size() << std::endl;
        fp = fopen(path.c_str(), "rb");  
        // int qtd =0;

        if( fp != NULL) {
            for (DeLIAData *Ddata : this->fDataGlobal){
                
                size_t fread_result;
                switch (Ddata->typeCode) {
                    case INT_CODE: {
                        fread_result =  fread(Ddata->data, sizeof(int), Ddata->sizeOfData, fp);
                        break;
                    }                
                    case DOUBLE_CODE: {
                        fread_result =  fread(Ddata->data, sizeof(double), Ddata->sizeOfData, fp);
                        break;
                    }                
                    case CHAR_CODE: {
                        fread_result =  fread(Ddata->data, sizeof(char), Ddata->sizeOfData, fp);
                        break;
                    }                
                    case FLOAT_CODE: {
                        fread_result =  fread(Ddata->data, sizeof(float), Ddata->sizeOfData, fp);
                        break;
                    }                
                    case BOOL_CODE: {
                        fread_result =  fread(Ddata->data, sizeof(bool), Ddata->sizeOfData, fp);
                        break;
                    }                
                    default:
                        std::cerr << "NO TYPE" << std::endl;
                        break;
                } 
                
                if (fread_result == 0) {
                    std::cerr << "Error while reading " << path  << std::endl;
                    fclose(fp);
                    return false;
                }               
            }
            fclose(fp); 
        }
    }

    std::string path = this->fPathFolder + "/DeLIA_gIteration.txt";
    fp = fopen(path.c_str(), "r"); 
    if(fp==NULL) {
        std::cerr << "Any DeLIA_gIteration data was saved"<< std::endl;
    } else {
        while(!feof(fp)) {
            fscanf(fp, "%d", &fTCurrent);
        }
        #ifdef VERBOSE
        if (fRead) std::cout << "GLOBAL DATA WAS SUCCESSFULLY READ IN " << id << std::endl;
        #endif
        fclose(fp);
    }

    return true;
}

/**
 * @brief Read local the local data;
 * each process will read its related data from the last execution
 *
 * @return true If all data were read ok.
 * @return false If all data were not read ok.
 */
bool Checkpointing::ReadLocalData() {
    int id = Utils::getId();
    for (IDataLocal *data : fIDataLocal) {
        std::string path = this->fPathFolder + 
                        "/DeLIA_Local_" + "node_" + std::to_string(id)+ 
                        "_gIteration_" + std::to_string(this->fTCurrent) +"_";

        if (!data->DeserializeLocal(path)) {
            return false;
        }
    }

    if (this->fDataLocal.size() >0) {
        FILE *fp;
        std::string path = this->fPathFolder+ "/DeLIA_LocalData_node_" + std::to_string(id)+ 
                        "_gIteration_" + std::to_string(this->fTCurrent) +".bin";
        fp = fopen(path.c_str(), "rb");  

        if( fp != NULL) {
            for (DeLIAData *Ddata : this->fDataLocal){
                size_t fread_result;
                switch (Ddata->typeCode) {
                    case INT_CODE: {
                        fread_result =  fread(Ddata->data, sizeof(int), Ddata->sizeOfData, fp);
                        break;
                    }                
                    case DOUBLE_CODE: {
                        fread_result =  fread(Ddata->data, sizeof(double), Ddata->sizeOfData, fp);
                        break;
                    }                
                    case CHAR_CODE: {
                        fread_result =  fread(Ddata->data, sizeof(char), Ddata->sizeOfData, fp);
                        break;
                    }                
                    case FLOAT_CODE: {
                        fread_result =  fread(Ddata->data, sizeof(float), Ddata->sizeOfData, fp);
                        break;
                    }
                    case BOOL_CODE: {
                        fread_result =  fread(Ddata->data, sizeof(bool), Ddata->sizeOfData, fp);
                        break;
                    }              
                    default:
                        std::cerr << "NO TYPE" << std::endl;
                        break;
                } 
                
                if (fread_result == 0) {
                    std::cerr << "Error while reading " << path  << std::endl;
                    fclose(fp);
                    return false;
                }               
            }
            #ifdef TEST
            std::cerr << "LOCAL_DATA_READ_SUCESS_IN_"<< id << std::endl;
            #endif

            fclose(fp);
        } 
    }

    if (fWorkloadScheduler != "DS") {
        if (fWorkloadScheduler == "CD") {
            if (id == fWorkloadSchedulerLeader) {
                return ReadAllTaks();
            }
        } else return ReadAllTaks();
    }  
    return true;
}


bool Checkpointing::isGlobalDataUpdated() {
    return fTCurrent == fTControl;
}

void Checkpointing::setIDataLocal(std::vector<IDataLocal *> data_local) {
    this->fIDataLocal = data_local;
}

void Checkpointing::setIDataGlobal(std::vector<IDataGlobal *> data_global) {
    this->fIDataGlobal = data_global;
}

void Checkpointing::setGlobalData(DeLIAData *global_data){
    this->fDataGlobal.push_back(global_data);
}

void Checkpointing::setLocalData(DeLIAData *local_data){
    fDataLocal.push_back(local_data);    
}

std::string Checkpointing::getPathFolder() {
    return fPathFolder;
}

bool Checkpointing::hasGlobalCheckpointing() {
    return !this->fIDataGlobal.empty();
}

int Checkpointing::getCurrentGlobalIteration(){
    return fTCurrent;
}

bool Checkpointing::hasLocalCheckpointing(){
    auto pos = fListLocalDataProcessed.find(fTCurrent);
    return (pos != fListLocalDataProcessed.end());
}

std::vector<DeLIAData*> Checkpointing::getListLocalData(){
    return this->fDataLocal;
}

void Checkpointing::clearListData(){
    this->fDataGlobal.clear();
    this->fDataLocal.clear();
}
