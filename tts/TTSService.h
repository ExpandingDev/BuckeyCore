#ifndef TTSSERVICEADAPTEE_H
#define TTSSERVICEADAPTEE_H

#include <stdint.h>
#include <string>
#include <vector>

#include "Service.h"

namespace Buckey {

class TTSService : public Buckey::Service {
    friend class TTSServiceAdapter;
    friend class TTSServiceProxy;
    public:
        virtual void speak(std::string words ) = 0;
        virtual void prepareSpeech(std::string words ) = 0;
        virtual void selectVoice(std::string voiceName ) = 0;
        virtual std::vector<std::string> getSpeechHistory(uint16_t index, uint8_t range ) = 0;
    	virtual std::string getState() = 0;
    	    
    	TTSService(std::string version, std::string name) : Buckey::Service(version, name) { };
   
   protected:
    	std::function<void(std::string)> voiceSwitchedCallback;
    	std::function<void(bool)> speechStateChangedCallback;
    	std::function<void(std::string)> speechPreparedCallback;        

};

}
#endif /* TTSSERVICEADAPTEE_H */
