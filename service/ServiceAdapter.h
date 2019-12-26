#ifndef SERVICEADAPTER_H
#define SERVICEADAPTER_H

#include <dbus-cxx.h>
#include <memory>
#include <stdint.h>
#include <string>

#include "Service.h"

namespace Buckey {
    class ServiceAdapter : public DBus::Object {
        friend class Service;
        protected:
            ServiceAdapter(Buckey::Service * adaptee, std::string path);
            DBus::signal<void, std::string>::pointer errorSignal;  
            DBus::signal<void, std::string>::pointer stateChangedSignal;            
            
        public:
            static std::shared_ptr<ServiceAdapter> create(Buckey::Service * adaptee, std::string path);
            static void signalError(Buckey::ServiceAdapter * a, std::string e);
            static void signalStateChange(Buckey::ServiceAdapter * a, Buckey::Service::StatusResponse s);
    };
}
#endif /* SERVICEADAPTER_H */
