/**
 * @file Main.cpp
 * @author Carla Santana (carla.ecomp@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2022-11-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <string>
#include <mpi.h>
// Including the FT_lib
#include "DeLIA.h"
#include "IDataGlobal.h"
#include "IDataLocal.h"
#include "LDClass.h"
#include "Settings.h"

int main (int argc, char *argv[]) {
  
  int  rank, comm_sz, size, iterations, value, initial_i;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  size = 10;
  iterations = atoi(argv[1]);
  // Initializing the string with the name of parameters file
  std::string inputfile = argv[2];
  LDClass *our_vector;
  // Initializing the LDClass
  our_vector = new LDClass(size);
  Settings *st;
  // Initializing the Settings
  st = new Settings(size);
  // Creating a vector of IDataGlobal
  std::vector <IDataGlobal*> data_global_ft;
  std::vector <IDataLocal*> data_local_ft;
  // Inserting a instance of LDClass in the vector of IDataGlobal
  data_global_ft.push_back(our_vector);
  data_local_ft.push_back(our_vector);
  
  // Initialization of Fault Tolerance
  DeLIA_Init(rank, comm_sz, inputfile, st, data_global_ft,data_local_ft); 
  // Check if there are data to be read with the current settings
  bool canRecover = DeLIA_CanRecoverGlobalCheckpointing();
  MPI_Barrier(MPI_COMM_WORLD);
  if(canRecover){    
    DeLIA_ReadGlobalData();
  } else {
    DeLIA_SaveSettings();
  }
  int i = DeLIA_getCurrentGlobalIteration();
  DeLIA_HeartbeatMonitoring_Init();
  for (i; i < iterations; i++) {
    our_vector->add(value);  
    MPI_Allreduce(our_vector->global_data, our_vector->local_data, 
                  size, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    // Moment that the Fault Tolerance can saves the global data
    DeLIA_SaveGlobalData();
    sleep(1);
  } 
  DeLIA_HeartbeatMonitoring_Finalize();
  DeLIA_Finalize();
  MPI_Finalize();
  delete our_vector;
  std::cout << "TEST FINALIZED OK" << std::endl;
}