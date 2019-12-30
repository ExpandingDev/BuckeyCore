#ifndef ASRSERVICEADAPTER_H
#define ASRSERVICEADAPTER_H

#include <dbus-cxx.h>
#include <memory>
#include <stdint.h>
#include <string>
#include "ASRService.h"
#include "ServiceAdapter.h"

namespace Buckey {
    class ASRServiceAdapter : public Buckey::ServiceAdapter {
        protected:
            ASRServiceAdapter(ASRService * adaptee, std::string path);
            
            DBus::signal<void>::pointer speechStartedSignal;
            DBus::signal<void>::pointer speechStoppedSignal;
            DBus::signal<void>::pointer listeningStartedSignal;
            DBus::signal<void>::pointer listeningStoppedSignal;
            DBus::signal<void,std::string>::pointer hypothesisSignal;
            DBus::signal<void,unsigned short>::pointer stateChangedSignal;
            
            static void signalSpeechStarted(ASRServiceAdapter * adapter);
            static void signalSpeechStopped(ASRServiceAdapter * adapter);
            static void signalListeningStarted(ASRServiceAdapter * adapter);
            static void signalListeningStopped(ASRServiceAdapter * adapter);
            static void signalHypothesis(ASRServiceAdapter * adapter, std::string hypothesis);
            static void signalStateChanged(ASRServiceAdapter * adapter, unsigned short state);            
            
        public:
            static std::shared_ptr<ASRServiceAdapter> create(ASRService * adaptee,std::string path);
    };
}
#endif /* ASRSERVICEADAPTER_H */
