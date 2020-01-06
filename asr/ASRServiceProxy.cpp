#include "ASRServiceProxy.h"

namespace Buckey {
    ASRServiceProxy::ASRServiceProxy(DBus::Connection::pointer conn, std::string dest, std::string path) : ServiceProxy(conn, dest, path){
        m_method_startListening = this->create_method<void>("ca.l5.expandingdev.Buckey.ASR","startListening");
        m_method_stopListening = this->create_method<void>("ca.l5.expandingdev.Buckey.ASR","stopListening");
    }

    std::shared_ptr<ASRServiceProxy> ASRServiceProxy::create(DBus::Connection::pointer conn, std::string dest, std::string path) {
        return std::shared_ptr<ASRServiceProxy>(new ASRServiceProxy(conn, dest, path));
    }

    void ASRServiceProxy::startListening(){
        (*m_method_startListening)();
    }

    void ASRServiceProxy::stopListening(){
        (*m_method_stopListening)();
    }
}
