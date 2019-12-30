#include "ASRServiceAdapter.h"

namespace Buckey {
    
    ASRServiceAdapter::ASRServiceAdapter(ASRService * adaptee, std::string path) : ServiceAdapter(adaptee, path) {
        DBus::MethodBase::pointer temp_method;
        temp_method = this->create_method<void,uint8_t>("ca.l5.expandingdev.Buckey.ASR", "setListeningBehavior",sigc::mem_fun( adaptee, &ASRService::setListeningBehavior));
        temp_method->set_arg_name(0, "type");
        
        temp_method = this->create_method<void,std::string>("ca.l5.expandingdev.Buckey.ASR", "setGrammar",sigc::mem_fun(adaptee, &ASRService::setGrammar));
        temp_method->set_arg_name(0, "jsgf");
        
        temp_method = this->create_method<void,std::string>( "ca.l5.expandingdev.Buckey.ASR", "setLanguageModel",sigc::mem_fun( adaptee, &ASRService::setLanguageModel ) );
        temp_method->set_arg_name(0, "lmpath");
        
        temp_method = this->create_method<void,std::string>( "ca.l5.expandingdev.Buckey.ASR", "setKeyword",sigc::mem_fun( adaptee, &ASRService::setKeyword ) );
        temp_method->set_arg_name(0, "keyword");
        
        temp_method = this->create_method<void,uint8_t>( "ca.l5.expandingdev.Buckey.ASR", "setRecognitionMode",sigc::mem_fun( adaptee, &ASRService::setRecognitionMode ) );
        temp_method->set_arg_name(0, "mode");
        
        temp_method = this->create_method<void>( "ca.l5.expandingdev.Buckey.ASR", "startListening",sigc::mem_fun(adaptee, &ASRService::startListening));
        
        temp_method = this->create_method<void>( "ca.l5.expandingdev.Buckey.ASR", "stopListening",sigc::mem_fun(adaptee, &ASRService::stopListening));
        
    }
    
    std::shared_ptr<ASRServiceAdapter> ASRServiceAdapter::create(ASRService * adaptee, std::string path) {
        return std::shared_ptr<ASRServiceAdapter>(new ASRServiceAdapter(adaptee, path));  
    }

}