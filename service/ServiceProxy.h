#ifndef SERVICEPROXY_H
#define SERVICEPROXY_H

#include <dbus-cxx.h>
#include <memory>
#include <stdint.h>
#include <string>

#include "Service.h"

namespace Buckey {
    class ServiceProxy : public DBus::ObjectProxy {

        public:
            static std::shared_ptr<ServiceProxy> create(DBus::Connection::pointer conn, std::string dest, std::string path);
            Buckey::Service::StatusResponse getStatus();
            
        protected:
            ServiceProxy(DBus::Connection::pointer conn, std::string dest, std::string path);
            DBus::MethodProxy<Buckey::Service::StatusResponse>::pointer  m_method_getStatus;
    };
}
#endif /* SERVICEPROXY_H */
