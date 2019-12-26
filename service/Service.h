#ifndef SERVICEADAPTEE_H
#define SERVICEADAPTEE_H

#include <stdint.h>
#include <string>
#include <atomic>

namespace Buckey{
    class Service {
        
        public:
            enum class State {
                RUNNING = 0, STOPPED = 1, ERROR = 2
            };        
        
            struct s_StatusResponse {
                unsigned int pid;
                std::string version;
                Buckey::Service::State state;
                std::string message;
                unsigned int code;
            };
            typedef struct s_StatusResponse StatusResponse;        
        
            virtual StatusResponse getStatus() = 0;
            
            static std::string generateStatusResponse(unsigned int pid, std::string version, Buckey::Service::State state, std::string message, unsigned int code);
            
            static std::string stateToString(Buckey::Service::State s);
            
            static Buckey::Service::State stateFromInt(int i);
            static int stateToInt(Buckey::Service::State);
            
            std::string getStatusString();
           
        protected:
            std::atomic<Buckey::Service::State> currentState;
            unsigned int pid;
            std::string version;
            std::string getStatusMessage();
            
            void changeState(Buckey::Service::State s);
            void signalError(std::string error);
            
        private:
            StatusResponse parseStatusResponse(std::string response);
    };
}
#endif /* SERVICEADAPTEE_H */
