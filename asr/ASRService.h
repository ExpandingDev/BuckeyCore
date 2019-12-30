#ifndef ASRSERVICEADAPTEE_H
#define ASRSERVICEADAPTEE_H

#include <stdint.h>
#include <string>
#include <functional>

#include "Service.h"

namespace Buckey {
    class ASRService : public Buckey::Service {
        enum class ListeningMode {
            CONTINUOUS = 0, PUSH_TO_SPEAK = 1, FILE = 2, STREAM = 3 
        };
        
        enum class RecognitionMode {
            JSGF = 0, LANGUAGE_MODEL = 1
        };
        
        friend class ASRServiceAdapter;
        public:
            virtual void setListeningBehavior(uint8_t types) = 0;
            virtual void setGrammar(std::string jsgf) = 0;
            virtual void setLanguageModel(std::string lmpath) = 0;
            virtual void setKeyword(std::string keyword) = 0;
            virtual void setRecognitionMode(uint8_t mode) = 0;
            virtual void startListening() = 0;
            virtual void stopListening() = 0;
            
            ASRService(std::string version, std::string name) : Buckey::Service(version, name) {  };
    
        protected:
            std::function<void(std::string)> hypothesisCallback;
            std::function<void(unsigned short)> stateChangedCallback;
            std::function<void()> speechStartedCallback;
            std::function<void()> speechStoppedCallback;
            std::function<void()> listeningStartedCallback;
            std::function<void()> listeningStoppedCallback;
    };
}
#endif /* ASRSERVICEADAPTEE_H */
