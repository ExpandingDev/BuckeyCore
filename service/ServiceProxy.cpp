#include "ServiceProxy.h"

Buckey::ServiceProxy::ServiceProxy(DBus::Connection::pointer conn, std::string dest, std::string path) : DBus::ObjectProxy(conn, dest, path){
    m_method_getStatus = this->create_method<std::string>("ca.l5.expandingdev.l5.Buckey.Service", "getStatus");
}

std::shared_ptr<Buckey::ServiceProxy> Buckey::ServiceProxy::create(DBus::Connection::pointer conn, std::string dest, std::string path ){
    return std::shared_ptr<Buckey::ServiceProxy>(new Buckey::ServiceProxy(conn, dest, path));
}

Buckey::Service::StatusResponse Buckey::ServiceProxy::getStatus() {
    return (*m_method_getStatus)();
}
