#ifndef DELIA_H
#define DELIA_H

#define NO_CODE     0
#define INT_CODE    1
#define DOUBLE_CODE 2
#define CHAR_CODE   3
#define FLOAT_CODE  4
#define BOOL_CODE   5

/// @cond
#include <iostream>
#include <vector>
/// @endcond

/**
 * @file DeLIA.h
 * @author Carla Santana (carla.ecomp@gmail.com)
 * @brief Main class of the DeLIA. Through it you can access the main features of the library
 * @version 1.0
 * @date 2022-10-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "IDataGlobal.h"
#include "IDataLocal.h"
#include "IDataSettings.h"

/**
 * @brief Initializing DeLIA
 * 
 * @param id ID of the process
 * @param comm_sz number of processes are involved in the execution
 * @param inputfile Path to the JSON file input with the main parameters of the library
 * @param settings IDataSettings that can check if 
 * there are checkpointing data from a last execution 
 * with the same configuration.
 * @param data_global Vector of IDataGlobal with all IDataGlobal used
 * @param data_local Vector of IDataLocal with all IDataLocal used
 */
void DeLIA_Init(int id, int comm_sz,
                std::string inputfile, 
                IDataSettings* settings, 
                std::vector<IDataGlobal*> data_global, 
                std::vector<IDataLocal*> data_local);

/**
 * @brief Initializing DeLIA
 * 
 * @param id ID of the process
 * @param comm_sz number of processes are involved in the execution
 * @param inputfile Path to the JSON file input with the main parameters of the library
 * @param settings IDataSettings that can check if 
 * there are checkpointing data from a last execution 
 * with the same configuration.
 * @param data_global Vector of IDataGlobal with all IDataGlobal used
 */
void DeLIA_Init(int id, int comm_sz,
                std::string inputfile, 
                IDataSettings* settings,
                std::vector<IDataGlobal*> data_global);

/**
 * @brief Initializing DeLIA
 * 
 * @param id ID of the process
 * @param comm_sz number of processes are involved in the execution
 * @param inputfile Path to the JSON file input with the main parameters of the library
 * @param settings IDataSettings that can check if 
 * there are checkpointing data from a last execution 
 * with the same configuration.
 * @param data_local Vector of IDataLocal with all IDataLocal used
 */
void DeLIA_Init(int id, int comm_sz,
                std::string inputfile, 
                IDataSettings* settings,
                std::vector<IDataLocal*> data_local);
/**
 * @brief Initializing DeLIA
 * 
 * @param id ID of the process
 * @param comm_sz number of processes are involved in the execution
 * @param inputfile Path to the JSON file input with the main parameters of the library
 * @param settings IDataSettings that can check if 
 * there are checkpointing data from a last execution 
 * with the same configuration.
 */ 
void DeLIA_Init(int id, int comm_sz,
                std::string inputfile, 
                IDataSettings* settings);
                
/**
 * @brief Initializing DeLIA
 * 
 * @param id ID of the process
 * @param comm_sz number of processes are involved in the execution
 * @param inputfile Path to the JSON file input with the main parameters of the library
 * @param configFile Config file that can check if 
 * there are checkpointing data from a last execution 
 * with the same configuration. 
 * @param configFile 
 */
void DeLIA_Init(int id, int comm_sz,
                std::string inputfile, 
                std::string configFile);

/**
 * @brief Initialization of the heartbeat monitoring 
 * The library creates threads that will monitor 
 * the operation of the other threads.
 * The type of heartbeat monitoring and the max time 
 * to wait for the threads' answer is set by the JSON 
 * input file.
 * 
 */
void DeLIA_HeartbeatMonitoring_Init();

/**
 * @brief Finalization of the sharing of the full local
 * data to the node neighbor. The library deletes the threads created to monitor
 * 
 */
void DeLIA_HeartbeatMonitoring_Finalize();

/**
 * @brief Save the global data
 */
void DeLIA_SaveGlobalData();

/**
 * @brief Save the local data from each process
 * 
 */
void DeLIA_SaveLocalData();

/**
 * @brief Read the local data, 
 * each processes will read its own local data from the last execution
 * 
 * @return true If all local data were read ok.
 * @return false If all local data were not read ok.
 */
bool DeLIA_ReadLocalData();

/**
 * @brief Return if there are global checkpointing data from a last execution
 * with the same configuration. If there are, FT can rollback.
 * 
 * @return true. If the it is possible read the global data.
 * @return false. If the it is not possible read the global data
 */
bool DeLIA_CanRecoverGlobalCheckpointing();

/**
 * @brief Read the global data, 
 * all processes will read the same global data from the last execution
 * 
 * @return true If all data were read ok.
 * @return false If all data were not read ok.
 */
bool DeLIA_ReadGlobalData();

/**
 * @brief Return if there are local checkpointing data from a last execution
 * with the same configuration. If there are, the process can roll back.
 * 
 * @param id 
 * @return true. If the it is possible read the global data.
 * @return false. If the it is not possible read the global data
 */
bool DeLIA_CanRecoverLocalCheckpointing();

/**
 * @brief Save the settings of the application
 * 
 */
void DeLIA_SaveSettings();

/**
 * @brief Check if the library can work
 * 
 * @return true. If all library configuration is ok, and library can work
 * @return false. If all library configuration is not ok, the library can not work 
 */
bool DeLIA_CanWork();

/**
 * @brief Set global data through the pointer of the variable
 * 
 * @param global_data 
 * @param size 
 * @param type 
 * @return true 
 * @return false 
 */
bool DeLIA_SetGlobalData(void *global_data, int size, int type);

/**
 * @brief Set local data through the pointer of the variable
 * 
 * @param local_data 
 * @param size 
 * @param type 
 * @return true 
 * @return false 
 */
bool DeLIA_SetLocalData(void *local_data, int size, int type);

/**
 * @brief Returns the current global iteration
 * 
 * @return int 
 */
int DeLIA_getCurrentGlobalIteration();

/**
 * @brief Finalize DeLIA
 * 
 */
void DeLIA_Finalize();

#endif // DELIA_H
