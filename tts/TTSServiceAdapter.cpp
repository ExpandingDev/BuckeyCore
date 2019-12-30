#include "TTSServiceAdapter.h"
namespace Buckey {
    TTSServiceAdapter::TTSServiceAdapter(TTSService * adaptee, std::string path) : ServiceAdapter(adaptee, path) {
        DBus::MethodBase::pointer temp_method;
        temp_method = this->create_method<void,std::string>( "ca.l5.expandingdev.Buckey.TTS", "speak",sigc::mem_fun( adaptee, &TTSService::speak ) );
        temp_method->set_arg_name( 0, "words" );
        
        temp_method = this->create_method<void,std::string>( "ca.l5.expandingdev.Buckey.TTS", "prepareSpeech",sigc::mem_fun( adaptee, &TTSService::prepareSpeech ) );
        temp_method->set_arg_name( 0, "words" );
        
        temp_method = this->create_method<void,std::string>( "ca.l5.expandingdev.Buckey.TTS", "selectVoice",sigc::mem_fun( adaptee, &TTSService::selectVoice ) );
        temp_method->set_arg_name( 0, "voiceFile" );
        
        temp_method = this->create_method<std::vector<std::string>,uint16_t,uint8_t>( "ca.l5.expandingdev.Buckey.TTS", "getSpeechHistory",sigc::mem_fun( adaptee, &TTSService::getSpeechHistory ) );
        temp_method->set_arg_name( 0, "return_value" );
        temp_method->set_arg_name( 1, "index" );
        temp_method->set_arg_name( 2, "range" );
        
        temp_method = this->create_method<std::string>( "ca.l5.expandingdev.Buckey.TTS", "getState",sigc::mem_fun( adaptee, &TTSService::getState ) );
        temp_method->set_arg_name( 0, "state" );
        
        speechPreparedSignal = this->create_signal<void, std::string>("ca.l5.expandingdev.Buckey.TTS", "SpeechPrepared");
        speechPreparedSignal->set_arg_name(0, "words");
        
        voiceSwitchedSignal = this->create_signal<void, std::string>("ca.l5.expandingdev.Buckey.TTS", "VoiceSwitched");
        voiceSwitchedSignal->set_arg_name(0, "voiceName");
        
        speechStartedSignal = this->create_signal<void>("ca.l5.expandingdev.Buckey.TTS", "SpeechStarted");
        speechStoppedSignal = this->create_signal<void>("ca.l5.expandingdev.Buckey.TTS", "SpeechStopped");
        
        adaptee->speechStateChangedCallback = std::bind(TTSServiceAdapter::signalSpeechStateChanged, this, std::placeholders::_1);
        adaptee->voiceSwitchedCallback = std::bind(TTSServiceAdapter::signalVoiceSwitched, this, std::placeholders::_1);
        adaptee->speechPreparedCallback = std::bind(TTSServiceAdapter::signalSpeechPrepared, this, std::placeholders::_1);
    
    }
    
    std::shared_ptr<TTSServiceAdapter> TTSServiceAdapter::create(TTSService * adaptee, std::string path ){
        return std::shared_ptr<TTSServiceAdapter>( new TTSServiceAdapter( adaptee, path ) );
    
    }
    
    void TTSServiceAdapter::signalVoiceSwitched(TTSServiceAdapter * a, std::string v) {
        a->voiceSwitchedSignal->emit(v);
    }
    
    void TTSServiceAdapter::signalSpeechStateChanged(TTSServiceAdapter * a, bool b) {
        if(b) {
            a->speechStartedSignal->emit();
        }
        else {
            a->speechStoppedSignal->emit();    
        }
    }
    
    void TTSServiceAdapter::signalSpeechPrepared(TTSServiceAdapter * a, std::string w) {
        a->speechPreparedSignal->emit(w);
    }

}