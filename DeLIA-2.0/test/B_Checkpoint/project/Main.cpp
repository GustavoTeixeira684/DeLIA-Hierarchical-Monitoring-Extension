/**
 * @file Main.cpp
 * @author Carla Santana (carla.ecomp@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <string>
#include <mpi.h>
#include <unistd.h>
#include "DeLIA.h"
#include "GDClass.h"
#include "Settings.h"

int main (int argc, char *argv[]) {
  
  int  rank, comm_sz, size, iterations;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  size = 10;
  iterations = atoi(argv[1]);
  GDClass *gd;
  // Initializing the GDClass
  gd = new GDClass(size);
  Settings *st;
  // Initializing the Settings
  st = new Settings(size);
  // Initializing the string with the name of parameters file
  std::string inputfile = "param.json";

  // Initialization of DeLIA
  DeLIA_Init(rank, comm_sz ,inputfile, st); 
  if (!DeLIA_CanWork()){
    std::cerr << "DeLIA can not work" << std::endl;
    exit;
  };
  DeLIA_SetGlobalData(gd->data_int, size, INT_CODE);
  DeLIA_SetGlobalData(gd->data_double, size, DOUBLE_CODE);
  DeLIA_SetGlobalData(gd->data_float, size, FLOAT_CODE);
  DeLIA_SetGlobalData(gd->data_char, 4, CHAR_CODE);
  // Check if there are data to be read with the current settings
  bool canRecover = DeLIA_CanRecoverGlobalCheckpointing();
  MPI_Barrier(MPI_COMM_WORLD);
  if(canRecover){    
    DeLIA_ReadGlobalData();
  } else {
    DeLIA_SaveSettings();
  }
  int i = DeLIA_getCurrentGlobalIteration();
  std::cout << i << std::endl;
  for (i; i < iterations; i++) {
    gd->add(i);  
    MPI_Allreduce(MPI_IN_PLACE, gd->data_int, size, MPI_INT, MPI_SUM,
                MPI_COMM_WORLD);
    // Moment that DeLIA can saves the global data
    DeLIA_SaveGlobalData();
    sleep(1);
  }
  gd->SaveFinalData(argv[2]);
  sleep(1);
  DeLIA_Finalize();
  MPI_Finalize();
  delete gd;
  std::cout << "TEST FINALIZED OK" << std::endl;
}