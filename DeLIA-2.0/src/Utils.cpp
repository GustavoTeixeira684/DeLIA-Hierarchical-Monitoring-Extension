#include"Utils.h"
Utils* Utils::instance = NULL;
int Utils::ID = -1;
int Utils::COMM_SZ= -1;

Utils* Utils::getInstanceUtils(){
    if (instance == nullptr) 
        instance = new Utils();
    
    return instance;
}

void Utils::releaseInstance() {
  if(nullptr != instance) {
    delete instance;
    instance = NULL;						
  }
}

int Utils::getId(){
  return ID;
}

int Utils::getComm_sz(){
  return COMM_SZ;
}

void Utils::setId(int id){
  ID = id;
}

void Utils::setComm_sz(int comm_sz){
  COMM_SZ = comm_sz;
}