#include"Utils.h"
Utils* Utils::instance = NULL;
int Utils::ID = -1;
int Utils::COMM_SZ= -1;
int Utils::ISSERVER = 0;
int Utils::MYSERVER = 0;
int Utils::NUMSERVERS = 0;
int *Utils::MYCLIENT = nullptr;
int Utils::SIZEMYCLIENT = 0;

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

int Utils::getSizeMyClient(){
  return SIZEMYCLIENT;
}

int Utils::isServer(){
  return ISSERVER;
}

int Utils::getMyServer(){
  return MYSERVER;
}

int *Utils::getMyClient(){
  return MYCLIENT;
}

int Utils::getNumServers(){
  return NUMSERVERS;
}

void Utils::setId(int id){
  ID = id;
}

void Utils::setNumServers(int num_servers){
  NUMSERVERS = num_servers;
}

void Utils::setComm_sz(int comm_sz){
  COMM_SZ = comm_sz;
}

void Utils::isServer(int isServer){
  this->ISSERVER = isServer;
}

void Utils::setMyServer(int myServer){
  this->MYSERVER = myServer;
}

void Utils::setMyClient(int *myClient, int num_clients){



  this->MYCLIENT = new int[num_clients];

  for(int i = 0; i < num_clients; i++){
      MYCLIENT[i] = myClient[i];
  }

  SIZEMYCLIENT = num_clients;

}
