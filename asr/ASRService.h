#ifndef ASRSERVICEADAPTEE_H
#define ASRSERVICEADAPTEE_H

#include <stdint.h>
#include <string>
#include <functional>

#include "Service.h"

namespace Buckey {
    class ASRService : public Buckey::Service {

        friend class ASRServiceAdapter;
        friend class ASRServiceProxy;
        public:
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
