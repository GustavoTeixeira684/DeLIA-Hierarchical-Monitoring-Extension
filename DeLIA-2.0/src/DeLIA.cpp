#include "../include/DeLIA.h"
#include <fstream>
#include <chrono>
#include <sys/stat.h>
#include "Utils.h"
#include "Checkpointing.h"
#include "FaultDetection.h"
#include "ApplicationSettings.h"
#include "DeLIAData.h"
#include "../libs/jsoncpp/json.h"
#include "../libs/jsoncpp/json-forwards.h"

bool fCanWork = false;
bool fFT = false;
bool canRecover = false;
Checkpointing *fCFT;
Utils *fUtil;
IDataSettings *settings;
bool ReadInputFile(std::string inputfile, IDataSettings *settings);

//!
//! Initialization of the Fault Tolerance
//! The FT will read the JSON file input and
//! set up the variables FT_FOLDER, CHECKPOINTING_TIME_GLOBAL, CHECKPOINTING_TIME_LOCAL,
//! TIME_MAX_WAIT, CHECKPOINTING_GLOBAL_ITERATION , TRIGGER_SIGNAL, TRIGGER_HEARTBEAT_MONITORING
//! and the IData.
//! If there are checkpointing data from a last execution
//! with the same configuration, FT will recover.
//!
void DeLIA_Init(int id, int comm_sz, std::string inputfile, IDataSettings *settings,
                               std::vector<IDataGlobal *> data_global,
                               std::vector<IDataLocal *> data_local) {
    fUtil = Utils::getInstanceUtils();
    fUtil->setComm_sz(comm_sz);
    fUtil->setId(id);
    canRecover = false;
    if (ReadInputFile(inputfile, settings))
    {
        fCFT->setIDataGlobal(data_global);
        fCFT->setIDataLocal(data_local);
    }
}

void DeLIA_Init(int id, int comm_sz, std::string inputfile, IDataSettings *settings,
                               std::vector<IDataGlobal *> data_global) {
    fUtil = Utils::getInstanceUtils();
    fUtil->setComm_sz(comm_sz);
    fUtil->setId(id);
    canRecover = false;
    if (ReadInputFile(inputfile, settings)) {
        fCFT->setIDataGlobal(data_global);
    }
}

void DeLIA_Init(int id, int comm_sz, std::string inputfile, IDataSettings *settings,
                               std::vector<IDataLocal *> data_local) {
    fUtil = Utils::getInstanceUtils();
    fUtil->setComm_sz(comm_sz);
    fUtil->setId(id);
    canRecover = false;
    if (ReadInputFile(inputfile, settings)) {
        fCFT->setIDataLocal(data_local);
    }
}

void DeLIA_Init(int id, int comm_sz,
                std::string inputfile, 
                IDataSettings* settings) {
    
    fUtil = Utils::getInstanceUtils();
    fUtil->setComm_sz(comm_sz);
    fUtil->setId(id);
    canRecover = false;
    if (ReadInputFile(inputfile, settings)) {
        fCFT->clearListData();
    }
}

void DeLIA_Init(int id, int comm_sz,
                std::string inputfile, 
                std::string configFile) {
    
    fUtil = Utils::getInstanceUtils();
    fUtil->setComm_sz(comm_sz);
    fUtil->setId(id);
    canRecover = false;
    ApplicationSettings* settings = new ApplicationSettings(configFile);
    if (ReadInputFile(inputfile, settings)) {
        fCFT->clearListData();
    }
}

bool DeLIA_SetGlobalData(void *global_data, int size, int type){

    if (!fCanWork) {
        std::cerr << "DeLIA can not work" << std::endl;
        return false; 
    }
    
    if (global_data == NULL || global_data == nullptr) {
        std::cerr << "DeLIA can not set global data, pointer null -- " << std::endl;
        return false; 
    } else {
        std::cerr << "DeLIA" << global_data << std::endl;
    }

    if (type != INT_CODE && type != DOUBLE_CODE &&
        type != CHAR_CODE && type != FLOAT_CODE) {

        std::cerr << "DATA TYPE INCORRECT TO DeLIA GD" << type<< std::endl;
        return false;
    }
    
    DeLIAData* ddata = new DeLIAData;
    (*ddata).data = global_data;
    (*ddata).sizeOfData = size;
    (*ddata).typeCode = type;
    
    fCFT->setGlobalData(ddata);
    return true;
}

bool DeLIA_SetLocalData(void *local_data, int size, int type){

    if (!fCanWork) {
        std::cerr << "DeLIA can not work" << std::endl;
        return false; 
    }
    
    if (type != INT_CODE && type != DOUBLE_CODE &&
        type != CHAR_CODE && type != FLOAT_CODE && 
        type != BOOL_CODE) {

        std::cerr << "DATA TYPE INCORRECT TO DeLIA LD" << std::endl;
        return false;
    }
    
    DeLIAData* ddata = new DeLIAData;
    (*ddata).data = local_data;
    (*ddata).sizeOfData = size;
    (*ddata).typeCode = type;
    
    fCFT->setLocalData(ddata);
    return true;
}

//!
//! Initialization of the heartbeat monitoring
//! Fault Detection creates threads that will monitor the operation of the other threads.
//! The type of heartbeat monitoring and the max time to wait
//! for the threads' answer is set by the JSON input file.
//!
void DeLIA_HeartbeatMonitoring_Init() {
    if (!fCanWork) {
        std::cerr << "DeLIA can not work" << std::endl;
        return; 
    }
    
    FaultDetection::RunHeartbeatMonitoring();
}

//!
//! Finalization of the heartbeat monitoring
//! Fault Detection deletes the threads created to monitor
//!
void DeLIA_HeartbeatMonitoring_Finalize() {
    if (!fCanWork) {
        std::cerr << "DeLIA can not work" << std::endl;
        return; 
    }
    FaultDetection::StopHeartbeatMonitoring();
}

//!
//! Save the global data
//! The serialization of the data is split between the processes.
//! Examples with 4 IDataGlobal :
//! If 4 processes are running, each will call "SerializeGlobal" from each IDataGlobal.
//! If 2 processes are running, each will call "SerializeGlobal" from 2 IDataGlobal.
//! If there is only 1 process, it will call "SerializeGlobal" from all IDataGlobal.
//! If there are more than 4 processes, the first 4 will call "SerializeGlobal" from each IDataGlobal.
//!
void DeLIA_SaveGlobalData() {
    if (!fCanWork) {
        std::cerr << "DeLIA can not work" << std::endl;
        return; 
    }

    #ifdef DEBUG
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    #endif

    fCFT->SaveGlobalData();

    #ifdef DEBUG
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    if (Utils::getId() == 0) {
        std::cout << "TIME_TO_SAVE_GLOBAL = " 
        << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() 
        << "[ns]" << std::endl;
    }
    #endif    
}

//!
//! Save the local data
//! Each process will serialize its own IDataLocal
//!
void DeLIA_SaveLocalData() {

    if (!fCanWork) {
        std::cerr << "DeLIA can not work" << std::endl;
        return; 
    }
    #ifdef DEBUG
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    #endif

    fCFT->SaveLocalData();

    #ifdef DEBUG
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    if (Utils::getId() == 0) {
        std::cout << "TIME_TO_SAVE_LOCAL = " 
        << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() 
        << "[ns]" << std::endl;
    }
    #endif
}

//!
//! Save the local data
//! Each process will serialize its own IDataLocal
//!
bool DeLIA_ReadLocalData() {

    if (!fCanWork) {
        std::cerr << "DeLIA can not work" << std::endl;
        return false; 
    }
    #ifdef DEBUG
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    #endif
    bool isRead = fCFT->ReadLocalData();

    #ifdef DEBUG
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << Utils::getId() << "ID_TIME_TO_READ_LOCAL = " 
    << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() 
    << "[ns]" << std::endl;        
    
    if (isRead) {
        std::cout << "DeLIA: Local Data read with sucess in "<< Utils::getId() << std::endl;
    } else {
        std::cerr << "DeLIA: Local Data not read with sucess in "<< Utils::getId() << std::endl;
    }    
    #endif

    return isRead;
}

bool DeLIA_CanRecoverGlobalCheckpointing() {
    if (!fCanWork) {
        std::cerr << "DeLIA can not work" << std::endl;
        return false; 
    }
    if (canRecover) {
        #ifdef DEBUG
        if (Utils::getId() == 0)
            std::cout << "Can recover last checkpointing global" << std::endl;
        #endif
        return true;
    } else {
        #ifdef DEBUG
        if (Utils::getId() == 0)
            std::cout << "Can not recover last checkpointing global" << std::endl;
        #endif
        return false;
    }
}

void DeLIA_SaveSettings() {
    if (!fCanWork) {
        std::cerr << "DeLIA can not work" << std::endl;
        return; 
    }
    #ifdef DEBUG
    if (Utils::getId() == 0) {
        std::cout << "============================================" << std::endl;
        std::cout << "-----\t FAULT TOLERANCE \t-----" << std::endl;
        std::cout << "-----\t Saving the current settings \t-----" << std::endl;
        std::cout << "============================================" << std::endl;
    }
    #endif
    if (Utils::getId() == 0)
        settings->SerializeSettings(fCFT->getPathFolder());
}

bool DeLIA_ReadGlobalData() {
    if (!fCanWork) {
        std::cerr << "DeLIA can not work" << std::endl;
        return false; 
    }

    #ifdef DEBUG
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    #endif
    bool isRead = fCFT->ReadGlobalData();

    #ifdef DEBUG
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    if (Utils::getId() == 0 ) {
        std::cout << Utils::getId() << "ID_TIME_TO_READ_GLOBAL = " 
        << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() 
        << "[ns]" << std::endl;        
    }

    if (isRead) {
        std::cout << "DeLIA: Global Data read with sucess in "<< Utils::getId() << std::endl;
    } else {
        std::cerr << "DeLIA: Global Data not read with sucess in "<< Utils::getId() << std::endl;
    }    
    #endif

    return isRead;
}

bool ReadInputFile(std::string inputfile, IDataSettings *settingsp) {
    settings = settingsp;
    std::string FT_FOLDER, TYPE_HB, WORKLOAD_SCHEDULER;
    int CHECKPOINTING_TIME_GLOBAL, CHECKPOINTING_TIME_LOCAL,
        TIME_MAX_WAIT, CHECKPOINTING_GLOBAL_ITERATION,
        SLEEP_THREAD_TIME, CHECKPOINTING_TIME_DIFF_LOCAL,
        TIME_SHARING_LOCAL_DATA_NEIGHBOR, WORKLOAD_SCHEDULER_LEADER;
    bool TRIGGER_SIGNAL;
    bool CHECKPOINTING_LOCAL_RECENT;
    Json::Value root;

    try
    {
        std::ifstream file(inputfile);
        file >> root;
        if (!root["FT_FOLDER"].isNull()) {
            FT_FOLDER = root["FT_FOLDER"].asString();
            struct stat buffer;
            if (stat(FT_FOLDER.c_str(), &buffer) != 0) {
                std::cout << "DeLIA folder invalid!";
                fCanWork=false;
                return false;
            }
        } else {
            fCanWork=false;
            std::cerr << "DeLIA folder invalid" << std::endl;
            return false;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "DeLIA config file invalid" << std::endl;
        fCanWork=false;
        return false;
    }

    if (!root["CHECKPOINTING_TIME_GLOBAL"].isNull()) {
        CHECKPOINTING_TIME_GLOBAL = root["CHECKPOINTING_TIME_GLOBAL"].asInt();
    } else {
        CHECKPOINTING_TIME_GLOBAL = -1;
    }

    if (!root["CHECKPOINTING_TIME_LOCAL"].isNull()) {
        CHECKPOINTING_TIME_LOCAL = root["CHECKPOINTING_TIME_LOCAL"].asInt();
    } else {
        CHECKPOINTING_TIME_LOCAL = -1;
    }

    if (!root["CHECKPOINTING_TIME_DIFF_LOCAL"].isNull()) {
        CHECKPOINTING_TIME_DIFF_LOCAL = root["CHECKPOINTING_TIME_DIFF_LOCAL"].asInt();
    } else {
        CHECKPOINTING_TIME_DIFF_LOCAL = -1;
    }

    if (!root["CHECKPOINTING_GLOBAL_ITERATION"].isNull()) {
        CHECKPOINTING_GLOBAL_ITERATION = root["CHECKPOINTING_GLOBAL_ITERATION"].asInt();
    } else {
        CHECKPOINTING_GLOBAL_ITERATION = -1;
    }

    if (!root["TRIGGER_SIGNAL"].isNull()) {
        TRIGGER_SIGNAL = root["TRIGGER_SIGNAL"].asBool();
        if (TRIGGER_SIGNAL)
            FaultDetection::TriggerSignal();
    } else {
        TRIGGER_SIGNAL = false;
    }

    if (!root["TRIGGER_HEARTBEAT_MONITORING"].isNull()) {
        if (!root["TRIGGER_HEARTBEAT_MONITORING"]["TIME_MAX_WAIT"].isNull())
            TIME_MAX_WAIT = root["TRIGGER_HEARTBEAT_MONITORING"]["TIME_MAX_WAIT"].asInt();

        if (!root["TRIGGER_HEARTBEAT_MONITORING"]["TYPE"].isNull()) {
            TYPE_HB = root["TRIGGER_HEARTBEAT_MONITORING"]["TYPE"].asString();
        } else {
            TYPE_HB = "LEADER";
        }

        if (!root["TRIGGER_HEARTBEAT_MONITORING"]["SLEEP_THREAD_TIME"].isNull()) {
            SLEEP_THREAD_TIME = root["TRIGGER_HEARTBEAT_MONITORING"]["SLEEP_THREAD_TIME"].asInt();
        } else {
            SLEEP_THREAD_TIME = 1;
        }
    } else {
        TIME_MAX_WAIT = -1;
        SLEEP_THREAD_TIME = -1;
    }

    if (!root["WORKLOAD_SCHEDULER"].isNull()) {
        WORKLOAD_SCHEDULER = root["WORKLOAD_SCHEDULER"].asString();
        if (WORKLOAD_SCHEDULER == "CD") {
            if (!root["WORKLOAD_SCHEDULER_LEADER"].isNull()) {
                WORKLOAD_SCHEDULER_LEADER = root["WORKLOAD_SCHEDULER_LEADER"].asInt();
            } else {
                WORKLOAD_SCHEDULER_LEADER = 0;
            }            
        } else {
            WORKLOAD_SCHEDULER_LEADER = -1;
        }         
    } else {
        WORKLOAD_SCHEDULER = "DS";
        WORKLOAD_SCHEDULER_LEADER = -1;
    }

    if (!root["TIME_SHARING_LOCAL_DATA_NEIGHBOR"].isNull()) {
        TIME_SHARING_LOCAL_DATA_NEIGHBOR = root["TIME_SHARING_LOCAL_DATA_NEIGHBOR"].asInt();
    } else {
        TIME_SHARING_LOCAL_DATA_NEIGHBOR = -1;
    }

    if (!root["CHECKPOINTING_LOCAL_RECENT"].isNull()) {
        CHECKPOINTING_LOCAL_RECENT = root["CHECKPOINTING_LOCAL_RECENT"].asBool();
    } else {
        CHECKPOINTING_LOCAL_RECENT = true;
    }

    FaultDetection::TriggerHeartbeatMonitoring(TYPE_HB, TIME_MAX_WAIT, SLEEP_THREAD_TIME);

    #ifdef VERBOSE
    if (Utils::getId() == 0) {
        std::cout << "============================================" << std::endl;
        std::cout << "-----\t FAULT TOLERANCE \t-----" << std::endl;
        std::cout << " FT_FOLDER \t\t\t\t = " << FT_FOLDER << std::endl;
        std::cout << " CHECKPOINTING_TIME_GLOBAL \t\t = " << CHECKPOINTING_TIME_GLOBAL << std::endl;
        std::cout << " CHECKPOINTING_TIME_LOCAL \t\t = " << CHECKPOINTING_TIME_LOCAL << std::endl;
        std::cout << " CHECKPOINTING_TIME_DIFF_LOCAL \t\t = " << CHECKPOINTING_TIME_DIFF_LOCAL << std::endl;
        std::cout << " CHECKPOINTING_GLOBAL_ITERATION \t = " << CHECKPOINTING_GLOBAL_ITERATION << std::endl;
        std::cout << " TIME_SHARING_LOCAL_DATA_NEIGHBOR \t = " << TIME_SHARING_LOCAL_DATA_NEIGHBOR << std::endl;
        std::cout << " CHECKPOINTING_LOCAL_RECENT \t\t = " << CHECKPOINTING_LOCAL_RECENT << std::endl;
        std::cout << " WORKLOAD_SCHEDULER \t\t\t  = " << WORKLOAD_SCHEDULER << std::endl;
        std::cout << " WORKLOAD_SCHEDULER_LEADER \t\t = " << WORKLOAD_SCHEDULER_LEADER << std::endl;
        std::cout << " TRIGGER_SIGNAL \t\t\t = " << TRIGGER_SIGNAL << std::endl;
        std::cout << " TRIGGER_HEARTBEAT_MONITORING:" << std::endl;
        std::cout << "\t TYPE \t\t\t\t = " << TYPE_HB << std::endl;
        std::cout << "\t TIME_MAX_WAIT\t\t\t = " << TIME_MAX_WAIT << std::endl;
        std::cout << "\t SLEEP_THREAD_TIME\t\t = " << SLEEP_THREAD_TIME << std::endl;
        std::cout << "============================================" << std::endl;
    }
    #endif

    fCFT = Checkpointing::getInstance();

    fCFT->setParameters(FT_FOLDER, CHECKPOINTING_TIME_GLOBAL, CHECKPOINTING_TIME_LOCAL,
                        CHECKPOINTING_TIME_DIFF_LOCAL,
                        CHECKPOINTING_GLOBAL_ITERATION, CHECKPOINTING_LOCAL_RECENT,
                        WORKLOAD_SCHEDULER, WORKLOAD_SCHEDULER_LEADER);

    fCanWork = true;
    canRecover = settings->CanRecover(fCFT->getPathFolder());
    return true;
}

bool DeLIA_CanRecoverLocalCheckpointing() {
    if (!fCanWork) {
        std::cerr << "DeLIA can not work" << std::endl;
        return false; 
    }
    int id = Utils::getId();

    if (canRecover) {
        #ifdef VERBOSE
        if (Utils::getId() == 0)
            std::cout << "Can recover last local checkpointing" << std::endl;
        #endif
        return fCFT->hasLocalCheckpointing();
    } else {
        #ifdef DEBUG
        if (Utils::getId() == 0)
            std::cout << "Can not recover last local checkpointing" << std::endl;
        #endif
        return false;
    }
}

bool DeLIA_CanWork() {
    return fCanWork;
}

int DeLIA_getCurrentGlobalIteration(){
    if (!fCanWork) {
        std::cerr << "DeLIA can not work" << std::endl;
        return -1; 
    }
    return fCFT->getCurrentGlobalIteration();
}

void DeLIA_Finalize() {
    fCFT->releaseInstance();
}