#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <iostream> 
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

class Utils {
    protected:
        static int ID, COMM_SZ, ISSERVER, MYSERVER, *MYCLIENT, SIZEMYCLIENT, NUMSERVERS;
        static Utils* instance;
        Utils(){};
        ~Utils(){};
    
    public:
        static Utils* getInstanceUtils();
        static void releaseInstance();
        static int getComm_sz();
        static int getId();
        static int isServer();
        static int getMyServer();
        static int *getMyClient();
        static int getSizeMyClient();
        static int getNumServers();
        void setComm_sz(int i);
        void setId(int i);
        void isServer(int i);
        void setMyServer(int i);
        void setNumServers(int i);
        void setMyClient(int *i, int num_clients);
};

#endif // UTILS_H