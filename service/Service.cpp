#include "Service.h"
#include <sstream>

void Buckey::Service::changeState(Buckey::Service::State s) {
    currentState.store(s);
    ///TODO: Send off a state changed event
}

void Buckey::Service::signalError(std::string error) {
    ///TODO: Send off an error signal
}

std::string Buckey::Service::generateStatusResponse(unsigned int pid, std::string version, Buckey::Service::State s, std::string message, unsigned int code) {
    ///TODO: Implement this
    std::string r = std::to_string(pid);
    r += "," + version + ",";
    r += std::to_string(Buckey::Service::stateToInt(s));
    r += "," + message + ",";
    r += std::to_string(code);
    return r;
}

Buckey::Service::StatusResponse Buckey::Service::parseStatusResponse(std::string response) {
    Buckey::Service::StatusResponse r;
    std::stringstream s(response);
    std::string parsed;
    unsigned short position = 0;
    //pid,version,status,message,status-code
    while(position < 5 ) {
        std::getline(s, parsed, ',');
        
        switch(position) {
            case 0: //pid
               r.pid = std::stoi(parsed);
            break;
            case 1: //version
                r.version = parsed;
            break;
            case 2: //status
                r.state = stateFromInt(std::stoi(parsed));
            break;
            case 3: //message
                r.message = parsed;
            break;
            case 4: //code
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
