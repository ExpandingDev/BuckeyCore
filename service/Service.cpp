#include "Service.h"
#include <sstream>

Buckey::Service::Service(std::string version, std::string name) {
    statusLock.lock();
    status.name = name;
    status.version = version;
    status.pid = 0;
    status.code = 200;
    status.message = "Default service status message";
    status.state = Buckey::Service::State::RUNNING;
    statusLock.unlock();
    setStateChangedCallback(Buckey::Service::emptyStateChangedCallback);
    setErrorCallback(Buckey::Service::emptyErrorCallback);
}

Buckey::Service::~Service() {
    
}

void Buckey::Service::setState(Buckey::Service::State s) {
    statusLock.lock();
    status.state = s;
    stateChangedCallback(status);
    statusLock.unlock();
}

void Buckey::Service::signalError(std::string error) {
    errorCallback(error);
}

void Buckey::Service::signalStatus() {
    //TODO: Implement this
        statusLock.lock();
        stateChangedCallback(status);
        statusLock.unlock();
}

std::string Buckey::Service::generateStatusResponse(StatusResponse r) {
    ///TODO: Implement this
    std::string s = std::to_string(r.pid);
    s += "," + r.name + + "," + r.version + ",";
    s += std::to_string(Buckey::Service::stateToInt(r.state));
    s += "," + r.message + ",";
    s += std::to_string(r.code);
    return s;
}

Buckey::Service::StatusResponse Buckey::Service::parseStatusResponse(std::string response) {
    Buckey::Service::StatusResponse r;
    std::stringstream s(response);
    std::string parsed;
    unsigned short position = 0;
    //pid,version,status,message,status-code
    while(position < 6 ) {
        std::getline(s, parsed, ',');
        
        switch(position) {
            case 0: //pid
               r.pid = std::stoi(parsed);
            break;
            case 1: //name
                r.name = parsed;
            break;
            case 2: //version
                r.version = parsed;
            break;
            case 3: //status
                r.state = stateFromInt(std::stoi(parsed));
            break;
            case 4: //message
                r.message = parsed;
            break;
            case 5: //code
                r.code = std::stoi(parsed);
            break;
            default:
            //Do nothing? Maybe complain?
            break;        
        }
        
        position++;
    }
    return r;
}

std::string Buckey::Service::stateToString(Buckey::Service::State s) {
    switch(s) {
        case Buckey::Service::State::RUNNING:
            return "RUNNING";
        break;
        case Buckey::Service::State::STOPPED:
            return "STOPPED";
        break;
        case Buckey::Service::State::ERROR:
            return "ERROR";
        break;
        default:
            return "UKNOWN_STATE";
        break;
    }
}

Buckey::Service::State Buckey::Service::stateFromInt(int i) {
    switch (i) {
        case 0:
            return Buckey::Service::State::RUNNING;
        break;
        case 1:
            return Buckey::Service::State::STOPPED;
        break;
        case 2:
            return Buckey::Service::State::ERROR;
        break;
        default:
            return Buckey::Service::State::ERROR;
        break;    
    }
}

int Buckey::Service::stateToInt(Buckey::Service::State s) {
    switch (s) {
        case Buckey::Service::State::RUNNING:
            return 0;
        break;
        case Buckey::Service::State::STOPPED:
            return 1;
        break;
        case Buckey::Service::State::ERROR:
            return 2;
        break;
        default:
            return 2;
        break;    
    }
}

Buckey::Service::StatusResponse Buckey::Service::getStatus() {
    Buckey::Service::StatusResponse r;
    statusLock.lock();
    r = status;
    statusLock.unlock();
    return r;
}

std::string Buckey::Service::getStatusString() {
    return Buckey::Service::generateStatusResponse(this->getStatus());
}

void Buckey::Service::setPID(unsigned int p) {
    statusLock.lock();
    status.pid = p;
    statusLock.unlock();
}

void Buckey::Service::setName(std::string n) {
    statusLock.lock();
    status.name = n;
    statusLock.unlock();
}

void Buckey::Service::setVersion(std::string v) {
    statusLock.lock();
    status.version = v;
    statusLock.unlock();
}

void Buckey::Service::setStatusCode(unsigned int c) {
    statusLock.lock();
    status.code = c;
    statusLock.unlock();
}

void Buckey::Service::setStatusMessage(std::string m) {
    statusLock.lock();
    status.message = m;
    statusLock.unlock();
}

void Buckey::Service::setStateChangedCallback(std::function<void(Buckey::Service::StatusResponse)> c) {
    stateChangedCallback = c;
}

void Buckey::Service::setErrorCallback(std::function<void(std::string)> c) {
    errorCallback = c;
}

void Buckey::Service::emptyStateChangedCallback(Buckey::Service::StatusResponse r) { }
void Buckey::Service::emptyErrorCallback(std::string e) { }
