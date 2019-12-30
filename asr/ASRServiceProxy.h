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
            void setListeningBehavior(uint8_t type);
            void setGrammar(std::string jsgf);
            void setLanguageModel(std::string lmpath);
            void setKeyword(std::string keyword);
            void setRecognitionMode(uint8_t mode);
            void startListening();
            void stopListening();
            
        protected:
            DBus::MethodProxy<void,uint8_t>::pointer m_method_setListeningBehavior;
            DBus::MethodProxy<void,std::string>::pointer m_method_setGrammar;
            DBus::MethodProxy<void,std::string>::pointer m_method_setLanguageModel;
            DBus::MethodProxy<void,std::string>::pointer m_method_setKeyword;
            DBus::MethodProxy<void,uint8_t>::pointer m_method_setRecognitionMode;
            DBus::MethodProxy<void>::pointer m_method_startListening;
            DBus::MethodProxy<void>::pointer m_method_stopListening;
    };
    
}
#endif /* ASRSERVICEPROXY_H */
