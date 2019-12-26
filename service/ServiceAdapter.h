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
        public:
            static std::shared_ptr<ServiceAdapter> create(Buckey::Service * adaptee, std::string path);
            void signalError(std::string e);
            void signalStateChange(Buckey::Service::State s);
    };
}
#endif /* SERVICEADAPTER_H */
