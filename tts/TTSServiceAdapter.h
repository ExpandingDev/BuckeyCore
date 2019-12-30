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
        TTSServiceAdapter(TTSService * adaptee, std::string path);
        
        static void signalSpeechStateChanged(TTSServiceAdapter * a, bool s);
        static void signalSpeechPrepared(TTSServiceAdapter * a, std::string s);
        static void signalVoiceSwitched(TTSServiceAdapter * a, std::string s);
        
        DBus::signal<void,std::string>::pointer speechPreparedSignal;
        DBus::signal<void>::pointer speechStartedSignal;
        DBus::signal<void>::pointer speechStoppedSignal;
        DBus::signal<void,std::string>::pointer voiceSwitchedSignal;

    public:
        static std::shared_ptr<TTSServiceAdapter> create(TTSService * adaptee, std::string path );
};

}
#endif /* TTSSERVICEADAPTER_H */
