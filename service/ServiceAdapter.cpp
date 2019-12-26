#include "ServiceAdapter.h"

Buckey::ServiceAdapter::ServiceAdapter(Buckey::Service * adaptee, std::string path) : DBus::Object(path){
    DBus::MethodBase::pointer temp_method;
    temp_method = this->create_method<std::string>("ca.l5.expandingdev.l5.Buckey.Service",  "getStatus",sigc::mem_fun(adaptee, &Buckey::Service::getStatusString));
    temp_method->set_arg_name(0, "status");

}

std::shared_ptr<Buckey::ServiceAdapter> Buckey::ServiceAdapter::create(Buckey::Service * adaptee, std::string path) {
    return std::shared_ptr<Buckey::ServiceAdapter>(new Buckey::ServiceAdapter(adaptee, path));
}

void Buckey::ServiceAdapter::signalError(std::string e) {
   // DBus::signal<void, std::string> s = 
}
