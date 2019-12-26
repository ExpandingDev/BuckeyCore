#ifndef SERVICEADAPTEE_H
#define SERVICEADAPTEE_H

#include <stdint.h>
#include <string>
#include <mutex>
#include <atomic>

#include "dbus-cxx.h"

namespace Buckey{
    class Service {
    	friend class ServiceProxy;

        public:
            enum class State {
                RUNNING = 0, STOPPED = 1, ERROR = 2
            };

            struct s_StatusResponse {
                unsigned int pid;
                std::string name;
                std::string version;
                Buckey::Service::State state;
                std::string message;
                unsigned int code;
            };
            typedef struct s_StatusResponse StatusResponse;
            
            //Status stuff
            void setPID(unsigned int p);
            void setVersion(std::string v);
            void setName(std::string n);
            void setStatusCode(unsigned int c);
            void setStatusMessage(std::string m);
            void setState(Buckey::Service::State s);
            
            //DBus stuff
            void signalError(std::string error);
            void signalStatus();
            void setErrorCallback(void (* callback)(std::string e));
            void setStateChangedCallback(void (* callback)(StatusResponse s));
            
            //Constructor and destructor
            Service(std::string version, std::string name);
            virtual ~Service();
            
            //Boilerplate/generate service funtions
            std::string getStatusString();
            StatusResponse getStatus();
            static std::string generateStatusResponse(StatusResponse r);            
            static std::string stateToString(Buckey::Service::State s);
            static Buckey::Service::State stateFromInt(int i);
            static int stateToInt(Buckey::Service::State);

        protected:
            StatusResponse status;
            std::mutex statusLock;
            
            void (* errorCallback)(std::string);
            void (* stateChangedCallback)(StatusResponse);
            
            static void emptyErrorCallback(std::string e);
            static void emptyStateChangedCallback(StatusResponse e);

        private:
            static StatusResponse parseStatusResponse(std::string response);
    };
}
#endif /* SERVICEADAPTEE_H */
