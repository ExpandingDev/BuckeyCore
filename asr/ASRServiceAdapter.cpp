#include "ASRServiceAdapter.h"
#include <functional>

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
        
        speechStartedSignal = this->create_signal<void>("ca.l5.expandingdev.Buckey.ASR", "SpeechStarted");
        speechStoppedSignal = this->create_signal<void>("ca.l5.expandingdev.Buckey.ASR", "SpeechStopped");
        listeningStartedSignal = this->create_signal<void>("ca.l5.expandingdev.Buckey.ASR", "ListeningStarted");
        listeningStoppedSignal = this->create_signal<void>("ca.l5.expandingdev.Buckey.ASR", "ListeningStopped");
        
        hypothesisSignal = this->create_signal<void, std::string>("ca.l5.expandingdev.Buckey.ASR", "Hypothesis");
        
        stateChangedSignal = this->create_signal<void, unsigned short>("ca.l5.expandingdev.Buckey.ASR", "StateChanged");
        
        
        adaptee->speechStartedCallback = std::bind(ASRServiceAdapter::signalSpeechStarted, this);
        adaptee->speechStoppedCallback = std::bind(ASRServiceAdapter::signalSpeechStopped, this);   
        adaptee->listeningStartedCallback = std::bind(ASRServiceAdapter::signalListeningStarted, this);
        adaptee->listeningStoppedCallback = std::bind(ASRServiceAdapter::signalListeningStopped, this);
        adaptee->hypothesisCallback = std::bind(ASRServiceAdapter::signalHypothesis, this, std::placeholders::_1);
        adaptee->stateChangedCallback = std::bind(ASRServiceAdapter::signalStateChanged, this, std::placeholders::_1); 
        
    }
    
    std::shared_ptr<ASRServiceAdapter> ASRServiceAdapter::create(ASRService * adaptee, std::string path) {
        return std::shared_ptr<ASRServiceAdapter>(new ASRServiceAdapter(adaptee, path));  
    }
    
    void ASRServiceAdapter::signalSpeechStarted(ASRServiceAdapter * a) {
        a->speechStartedSignal->emit();
    }
    
    void ASRServiceAdapter::signalSpeechStopped(ASRServiceAdapter * a) {
        a->speechStoppedSignal->emit();
    }
    
    void ASRServiceAdapter::signalListeningStarted(ASRServiceAdapter * a) {
        a->listeningStartedSignal->emit();
    }
    
    void ASRServiceAdapter::signalListeningStopped(ASRServiceAdapter * a) {
        a->listeningStoppedSignal->emit();
    }
    
    void ASRServiceAdapter::signalHypothesis(ASRServiceAdapter * a, std::string hypothesis) {
        a->hypothesisSignal->emit(hypothesis);
    }
    
    void ASRServiceAdapter::signalStateChanged(ASRServiceAdapter * a, unsigned short state) {
        a->stateChangedSignal->emit(state);
    }

}