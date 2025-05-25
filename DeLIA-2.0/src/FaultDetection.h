#ifndef FAULTDETECTION_H
#define FAULTDETECTION_H

#include <string.h>
#include <iostream> 
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctime>
#include <list>
#include <pthread.h>
#include "Utils.h"
#include "Checkpointing.h"

#define PORT    8080
#define MAXLINE 10

class FaultDetection {
    private:
        static void Client();
        static void Server(time_t* nodes_answer);
        static void *RunThread(void* id);
        static void Handler(int sig); 
    
    public:
        FaultDetection();
        static void TriggerHeartbeatMonitoring(std::string type, int waiting_time, int sleep_thread_time);
        static void TriggerSignal();
        static void RunHeartbeatMonitoring();
        static void StopHeartbeatMonitoring();
        
        ~FaultDetection() {}
};

#endif // FAULTDETECTION_H
