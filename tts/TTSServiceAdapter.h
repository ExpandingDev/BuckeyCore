#ifndef TTSSERVICEADAPTER_H
#define TTSSERVICEADAPTER_H

#include <dbus-cxx.h>
#include <memory>
#include <stdint.h>
#include <string>
#include <vector>

#include "ServiceAdapter.h"

#include "TTSService.h"

namespace Buckey {

class TTSServiceAdapter : public Buckey::ServiceAdapter {
    protected:
        TTSServiceAdapter(Buckey::TTSService * adaptee, std::string path);
        
        static void signalSpeechStateChanged(Buckey::TTSServiceAdapter * a, bool s);
        static void signalSpeechPrepared(Buckey::TTSServiceAdapter * a, std::string s);
        static void signalVoiceSwitched(Buckey::TTSServiceAdapter * a, std::string s);
        
        DBus::signal<void,std::string>::pointer speechPreparedSignal;
        DBus::signal<void>::pointer speechStartedSignal;
        DBus::signal<void>::pointer speechStoppedSignal;
        DBus::signal<void,std::string>::pointer voiceSwitchedSignal;

    public:
        static std::shared_ptr<Buckey::TTSServiceAdapter> create(Buckey::TTSService * adaptee, std::string path );
};

}
#endif /* TTSSERVICEADAPTER_H */
