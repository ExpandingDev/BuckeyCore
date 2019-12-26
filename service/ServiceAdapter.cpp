#include "ServiceAdapter.h"
#include <functional>

Buckey::ServiceAdapter::ServiceAdapter(Buckey::Service * adaptee, std::string path) : DBus::Object(path){
    DBus::MethodBase::pointer temp_method;
    temp_method = this->create_method<std::string>("ca.l5.expandingdev.l5.Buckey.Service",  "getStatus",sigc::mem_fun(adaptee, &Buckey::Service::getStatusString));
    temp_method->set_arg_name(0, "status");
    
    errorSignal = this->create_signal<void, std::string>("ca.l5.expandingdev.Buckey.Service", "Error");
    errorSignal->set_arg_name(0, "message");
    
    stateChangedSignal = this->create_signal<void, std::string>("ca.l5.expandingdev.Buckey.Service", "StateChanged");
    stateChangedSignal->set_arg_name(0, "status");
    
    adaptee->setErrorCallback(std::bind(&Buckey::ServiceAdapter::signalError, this, std::placeholders::_1));
    adaptee->setStateChangedCallback(std::bind(&Buckey::ServiceAdapter::signalStateChange, this, std::placeholders::_1));
}

std::shared_ptr<Buckey::ServiceAdapter> Buckey::ServiceAdapter::create(Buckey::Service * adaptee, std::string path) {
    return std::shared_ptr<Buckey::ServiceAdapter>(new Buckey::ServiceAdapter(adaptee, path));
}

void Buckey::ServiceAdapter::signalError(Buckey::ServiceAdapter * a, std::string e) {
    a->errorSignal->emit(e);
}

void Buckey::ServiceAdapter::signalStateChange(Buckey::ServiceAdapter * a, Buckey::Service::StatusResponse r) {
    a->stateChangedSignal->emit(Buckey::Service::generateStatusResponse(r));
}
