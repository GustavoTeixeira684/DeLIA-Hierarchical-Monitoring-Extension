#include "FaultDetection.h"

int fWaitingTime;
int fSleepThreadTime;
bool fThreadWorking;
int type;
bool fSignalReceive;
std::unordered_map<int, time_t> clients_answer;

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
    
    time_t now;

    pthread_t wd_thread;
    if(Utils::isServer()){
        time(&now);
        for (int i = 0; i < Utils::getSizeMyClient(); i++) {
            clients_answer[Utils::getMyClient()[i]] = now;
        }
        pthread_create(&wd_thread, NULL, RunServer, NULL);
    }

    while(fThreadWorking){
        Client();
        sleep(fSleepThreadTime);
    }

    if(Utils::isServer()){
        pthread_join(wd_thread, nullptr);
    }
    pthread_exit(NULL);

}

void *FaultDetection::RunServer(void* arg){
    while(fThreadWorking){
        Server(clients_answer);
    }
    pthread_exit(NULL);
}

void FaultDetection::Client() {
    int sockfd;
    char buffer[MAXLINE];
    std::string message = std::to_string(Utils::getId());
    char hello[message.size() + 1];
    strcpy(hello, message.c_str());
    int id = Utils::getId();

    
    int portaClients = PORT + Utils::getNumServers() + 1;

    
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    
    int reuse = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0 ) {
        perror("setsockopt SO_REUSEADDR/SO_REUSEPORT");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    
    sockaddr_in cliaddr{};
    cliaddr.sin_family      = AF_INET;
    cliaddr.sin_addr.s_addr = INADDR_ANY;
    cliaddr.sin_port        = htons(portaClients);

    if (bind(sockfd, reinterpret_cast<sockaddr*>(&cliaddr), sizeof(cliaddr)) < 0) {
        perror("bind to portaClients failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    
    sockaddr_in servaddr{};
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port        = htons(PORT + Utils::getMyServer());

    int sent= sendto(sockfd, hello, strlen(hello), MSG_CONFIRM,
           reinterpret_cast<sockaddr*>(&servaddr), sizeof(servaddr));

    if (sent<0){     
        for(int retryServer=0;retryServer<3;retryServer++){
            sent=sendto(sockfd, hello, strlen(hello), MSG_CONFIRM,
            reinterpret_cast<sockaddr*>(&servaddr), sizeof(servaddr));            
            if(sent >=0){
                break;
            }
        }
    }
    
    struct timeval read_timeout{1, 1000};  // 1s e 1000µs
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &read_timeout, sizeof(read_timeout));

    for (int attempt = 0; attempt < 3; ++attempt) {
        socklen_t len = sizeof(servaddr);
        int n = recvfrom(sockfd, buffer, MAXLINE, 0,
                         reinterpret_cast<sockaddr*>(&servaddr), &len);
        if (n > 0) {
            buffer[n] = '\0';
            int id_rcv = std::atoi(buffer);

            if (id_rcv == Utils::getId()) {
                // ecoa de volta se for loop de detecção de falha
                sendto(sockfd, hello, strlen(hello), MSG_CONFIRM,
                       reinterpret_cast<sockaddr*>(&servaddr), sizeof(servaddr));
            } else {
                #ifdef TEST
                std::cerr << "OBSERVED_NODE_" << id  << "_RECEIVES_TRIGGER" << std::endl; 
                std::cerr << "MSG_RECEIVED_" << id  << "_:_" << id_rcv << std::endl; 
                #endif
                Checkpointing::getInstance()->SaveLocalData();
                break;
            }
        }
        // se timeout, repete até 3 tentativas
    }

    close(sockfd);
}

// void FaultDetection::Server(time_t* nodes_answer){
void FaultDetection::Server(std::unordered_map<int,time_t> clients_answer){
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
    servaddr.sin_port = htons(PORT+Utils::getId()); // Regra para ouvir apenas os seus clientes

    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    // Em Linux moderno, se precisar de múltiplos binds simultâneos:
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
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

    
    int id_rcv;
    time_t now;
    if(n > 0){
        buffer[n] = '\0';
        #ifdef DEBUGHEARTBEATMSG
        std::cerr << "Msg from the observed node :" << buffer << std::endl;
        #endif
        id_rcv = atoi(buffer);
        time(&now);    
        clients_answer[id_rcv] = now;

    }else{
        time(&now);
    }

    
    for(const auto& par : clients_answer){
        if(par.first != id_rcv){
            double diff_time = difftime(now, par.second);
            if (diff_time > fWaitingTime || fSignalReceive) {
                #ifdef TEST
                std::cerr << "NODE_" << par.first << "_DO_NOT_ANSWER" << std::endl;
                #endif
                Checkpointing::getInstance()->SaveLocalData();
                #ifdef TEST
                std::cerr << "SEND_TRIGGER_TO_ALL_NODES BY ID: "<<std::to_string(Utils::getId()) << std::endl;
                #endif
                std::string message;
                if (fSignalReceive) message = std::to_string(-1);           
                else{
                    message=std::to_string(Utils::getId());
                }
                strcpy(hello, message.c_str());
                
                int broadcastEnable=1;
                
                // --- Envio de trigger aos clientes numa porta fixa ---
                
                int portaClients = PORT + Utils::getNumServers() + 1;
                int ret = 0;

                cliaddr.sin_family      = AF_INET;
                cliaddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
                cliaddr.sin_port        = htons(portaClients);

                for(int i = 0; i < 3; i++){

                    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
                    ret = sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);

                    #ifdef DEBUGHEARTBEATMSG
                    std::cerr << "TRY 1 BROADCAST => RETURN SENDTO " << ret <<std::endl;
                    #endif

                    if (ret > 0) {
                        fSignalReceive=false;
                        break;          
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