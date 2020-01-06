#ifndef ASRSERVICEPROXY_H
#define ASRSERVICEPROXY_H

#include <dbus-cxx.h>
#include <memory>
#include <stdint.h>
#include <string>

#include "ServiceProxy.h"
namespace Buckey {

    class ASRServiceProxy : public Buckey::ServiceProxy {
        protected:
            ASRServiceProxy(DBus::Connection::pointer conn, std::string dest, std::string path);

        public:
            static std::shared_ptr<ASRServiceProxy> create(DBus::Connection::pointer conn, std::string dest, std::string path);
            void startListening();
            void stopListening();

        protected:
            DBus::MethodProxy<void>::pointer m_method_startListening;
            DBus::MethodProxy<void>::pointer m_method_stopListening;
    };
}
#endif /* ASRSERVICEPROXY_H */
