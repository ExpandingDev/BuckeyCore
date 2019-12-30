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
        public:
            static std::shared_ptr<ASRServiceAdapter> create(ASRService * adaptee,std::string path);
    };
}
#endif /* ASRSERVICEADAPTER_H */
