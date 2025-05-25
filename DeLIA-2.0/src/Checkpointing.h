#ifndef CHECKPOINTING_H
#define CHECKPOINTING_H
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include <ctime>
#include <stdexcept>
#include "../include/IDataGlobal.h"
#include "../include/IDataLocal.h"
#include "DeLIAData.h"
#include "Utils.h"
/**
 * @brief class is an singleton to ensure that all other classes 
 * that use it will be dealing with the same instance with the same settings.
 * 
 */
class Checkpointing {

    private:
        bool fRead;
        bool fDDataUsed;
        bool fCheckpointingLocalRecent;
        std::vector<IDataGlobal*> fIDataGlobal;
        std::vector<IDataLocal*> fIDataLocal;
        std::vector<DeLIAData*> fDataGlobal;
        std::vector<DeLIAData*> fDataLocal;
        std::vector<DeLIAData*> fDataLocalNeighbor;
        std::set<int> fListLocalDataProcessed;
        std::string fPathFolder;
        std::string fWorkloadScheduler;
        int fWorkloadSchedulerLeader;
        int fCheckpointingGlobalTime;
        int fCheckpointingLocalTime;
        int fCheckpointingLocalTimeDiff;
        int fCheckpointingGlobalIteration;
        int fCheckpointingGlobalLastIteration;
        time_t fLastGlobalCheckpointingTime;
        time_t fLastLocalCheckpointingTime;
        int fTControl;
        int fTCurrent=0;

    protected:
        static Checkpointing* instance;
        Checkpointing(){
            fDDataUsed = false;
        };
        ~Checkpointing(){
            fIDataGlobal.clear();
            fIDataLocal.clear();
            fDataGlobal.clear();
            fDataLocal.clear();
            fDataLocalNeighbor.clear();
            fListLocalDataProcessed.clear();
        };

    public:
        
        static Checkpointing* getInstance();
        static void releaseInstance();
        void setParameters(std::string ft_folder, int checkpointing_global_time, 
                        int checkpointing_local_time, int checkpointing_local_time_diff, 
                        int checkpointing_global_iteration, bool checkpointing_local_recent,
                        std::string workload_scheduler, int workload_scheduler_leader);
        void setIDataLocal(std::vector<IDataLocal*> data_local);
        void setIDataGlobal(std::vector<IDataGlobal*> data_global);
        bool hasGlobalCheckpointing();
        bool hasLocalCheckpointing();
        std::string getPathFolder();
        void SaveGlobalData();
        void SaveLocalData();  
        void SaveTasks();
        bool ReadGlobalData();
        bool ReadLocalData();
        bool ReadAllTaks();
        bool isGlobalDataUpdated();
        int getCurrentGlobalIteration();
        std::vector<DeLIAData*> getListLocalData();
        void clearListData();
        void setGlobalData(DeLIAData *global_data);
        void setLocalData(DeLIAData *local_data);
};

#endif // CHECKPOINTING_H
