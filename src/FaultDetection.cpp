#include "FaultDetection.h"

int fWaitingTime;
int fSleepThreadTime;
bool fThreadWorking;
int type;
bool fSignalReceive;

struct sWdData {
  int  id_server;
}; typedef struct sWdData wdData;
wdData *wd_data;

void FaultDetection::TriggerSignal() {
    fSignalReceive= false;
    signal(SIGCONT, Handler);  
    signal(SIGTERM, Handler);
    signal(SIGSTOP, Handler); 
    signal(SIGTSTP, Handler);    
}

void FaultDetection::TriggerHeartbeatMonitoring(std::string type, int waiting_time, int sleep_thread_time) {
    fWaitingTime = waiting_time;
    fSleepThreadTime = sleep_thread_time;
    fThreadWorking = true;    
}

void FaultDetection::RunHeartbeatMonitoring() {
    if(fWaitingTime == -1) return;
    if(Utils::getComm_sz() == 1) return;

    pthread_t wd_thread[2];    

    int rc = pthread_create(&wd_thread[0], NULL, RunThread, (void *)wd_data);

    if (rc) {
        std::cerr << "Error:unable to create thread," << rc << std::endl;
        exit(-1);
    }    
}

void FaultDetection::StopHeartbeatMonitoring() {
    if(fWaitingTime == -1) return;
    if(Utils::getComm_sz() == 1) return;
    fThreadWorking = false;
}

void *FaultDetection::RunThread(void* data) {
    wdData *wd_data;
    wd_data = ( wdData *) data;
    
    time_t* nodes_answer = new time_t[Utils::getComm_sz()];
    time_t now;
    time(&now);
    for (int i = 0; i < Utils::getComm_sz(); i++) {
        nodes_answer[i] = now;
    }
    
    while (fThreadWorking) {        
        if (Utils::getId() == 0) {
            Server(nodes_answer);
        } else {            
            Client();            
            sleep(fSleepThreadTime);            
        }
    }
    pthread_exit(NULL);
}

void FaultDetection::Client() {
    
    int sockfd;
    char buffer[MAXLINE];
    std::string message;
    int id = Utils::getId();
    message = std::to_string(id);
    char hello[message.length() + 1]; 
 
    strcpy(hello, message.c_str());
    struct sockaddr_in     servaddr;
  
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
  
    memset(&servaddr, 0, sizeof(servaddr));
      
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
      
    int n;
    unsigned int len;
      
    sendto(sockfd, (const char *)hello, strlen(hello),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
            sizeof(servaddr));

    #ifdef DEBUGHEARTBEATMSG
    std::cerr << "Observed node " << id << " send msg to Leader node" << std::endl;
    #endif

    struct timeval read_timeout;
    read_timeout.tv_sec = 1;
    read_timeout.tv_usec = 1000;

    for (int i = 0; i < 3; i++) {
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &read_timeout, sizeof read_timeout);
    
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                    MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
        buffer[n] = '\0';
        int id_rcv = atoi(buffer);
        if (strlen(buffer) != 0) {
            if (id_rcv == Utils::getId()) {
                
                #ifdef DEBUGHEARTBEATMSG
                std::cerr << "Observed node " << id  << " detected wrong" << std::endl;
                #endif

                sendto(sockfd, (const char *)hello, strlen(hello),
                        MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
                        sizeof(servaddr));
            } else {
                
                #ifdef TEST
                std::cerr << "OBSERVED_NODE_" << id  << "_RECEIVES_TRIGGER" << std::endl; 
                std::cerr << "MSG_RECEIVED_" << id  << "_:_" << id_rcv << std::endl; 
                #endif

                Checkpointing::getInstance()->SaveLocalData();
                break;
                // sleep(10);
            }
        } 
        #ifdef DEBUGHEARTBEATMSG
        else {
            std::cerr << "Observed node " << id  << " do not receive any trigger" << std::endl; 
        }
        #endif
    }    

    close(sockfd);
    return;
}

void FaultDetection::Server(time_t* nodes_answer){
   
    int sockfd;
    char buffer[MAXLINE];
    char hello[] = {"1"};
    struct sockaddr_in servaddr, cliaddr;
      
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
      
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
      
    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
      
    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
            sizeof(servaddr)) < 0 ) {
        perror("bind failed");
        return;
    }
      
    int n;
    unsigned int len;
    
    len = sizeof(cliaddr);  //len is value/resuslt
    struct timeval read_timeout;
    read_timeout.tv_sec = 1;
    read_timeout.tv_usec = 1000;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &read_timeout, sizeof read_timeout);
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);

    buffer[n] = '\0';
    
    #ifdef DEBUGHEARTBEATMSG
    std::cerr << "Msg from the observed node :" << buffer << std::endl;
    #endif
    int id_rcv = atoi(buffer);

    time_t now;

	time(&now);
    
    nodes_answer[id_rcv] = now;
    nodes_answer[Utils::getId()] = now;
    
    for (int i = 0; i < Utils::getComm_sz(); i++) {
        if (i != Utils::getId() && i != id_rcv){
            double diff_time = difftime(now, nodes_answer[i]);
            if (diff_time > fWaitingTime || fSignalReceive) {
                #ifdef TEST
                std::cerr << "NODE_" << i << "_DO_NOT_ANSWER" << std::endl;
                #endif
                Checkpointing::getInstance()->SaveLocalData();
                #ifdef TEST
                std::cerr << "SEND_TRIGGER_TO_ALL_NODES" << std::endl;
                #endif
                std::string message;
                if (fSignalReceive) message = std::to_string(-1);            
                else message = std::to_string(i);            
                strcpy(hello, message.c_str());
                
                int broadcastEnable=1;
                setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
                
                int ret=sendto(sockfd, (const char *)hello, strlen(hello), 
                        MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
                            len);
                #ifdef DEBUGHEARTBEATMSG
                std::cerr << "TRY 1 BROADCAST => RETURN SENDTO " << ret <<std::endl;
                #endif
                if (ret <0) {
                    for (int i = 2; i < 4; i++) {
                        int broadcastEnable=1;
                        setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
                        
                        ret=sendto(sockfd, (const char *)hello, strlen(hello), 
                                MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
                                    len);
                        #ifdef DEBUGHEARTBEATMSG
                        std::cerr << "TRY "<< i <<" BROADCAST => RETURN SENDTO " << ret <<std::endl;
                        #endif
                        if (ret > 0) {
                            fSignalReceive=false;
                            break;          
                        } 
                    }
                    
                }
                
                            
                break;
            }
        }
    }
    close(sockfd);    
}

void FaultDetection::Handler(int sig) {
    std::cerr << "SIGNAL_RECEIVED_" << sig << "_IN_RANK_" << Utils::getId() << std::endl;
    Checkpointing::getInstance()->SaveLocalData();
    if (sig == SIGTERM) {
        fSignalReceive =  true;
        std::cerr << "SIGTERM RECEIVED, CLOSING DeLIA" << std::endl;
    }    
} 