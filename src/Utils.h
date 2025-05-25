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
        static int ID, COMM_SZ;
        static Utils* instance;
        Utils(){};
        ~Utils(){};
    
    public:
        static Utils* getInstanceUtils();
        static void releaseInstance();
        static int getComm_sz();
        static int getId();
        void setComm_sz(int i);
        void setId(int i);
};

#endif // UTILS_H