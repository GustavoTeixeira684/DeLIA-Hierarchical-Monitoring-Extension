// including the IDataGlobal
#include "IDataGlobal.h"
#include "IDataLocal.h"
#include "DeLIA.h"
#include <unistd.h>

// Indicating that LDClass implements IDataGlobal
class LDClass: public IDataGlobal, public IDataLocal
{
    private:
        // Initializing the variable from IDataGlobal
        std::string global_data_filename = "global_data_example.bin";
        std::string local_data_filename = "local_data_example.bin";
    
    public:
        // Variable from the own class
        int *global_data; // important data to all execution
        int *local_data; // important data to each process
        int size; // size of data
        int last_i_local;
        int i_global;
    
    public:
        // Functions from the own class
        LDClass(int size);
        ~LDClass();
        void add(int value);
        // Declaring the functions from IDataGlobal
        void SerializeGlobal(std::string ft_path);
        bool DeserializeGlobal(std::string ft_path);
        std::string const getName(){return "LDClass";}
        #ifdef TEST
        bool TestRecoverGlobal(std::string ft_path);
        #endif
        
        // Declaring the functions from IDataLocal
        void SerializeLocal(std::string ft_path);
        bool DeserializeLocal(std::string ft_path);
        void SerializeTasks(std::string ft_path){};
        bool DeserializeAllTaks(std::string ft_path){return true;};
        #ifdef TEST
        bool TestRecoverLocal(std::string ft_path);
        #endif

};