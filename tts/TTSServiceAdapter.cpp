#include "TTSServiceAdapter.h"

Buckey::TTSServiceAdapter::TTSServiceAdapter(Buckey::TTSService * adaptee, std::string path) : Buckey::ServiceAdapter(adaptee, path) {
    DBus::MethodBase::pointer temp_method;
    temp_method = this->create_method<void,std::string>( "ca.l5.expandingdev.Buckey.TTS", "speak",sigc::mem_fun( adaptee, &Buckey::TTSService::speak ) );
    temp_method->set_arg_name( 0, "words" );
    
    temp_method = this->create_method<void,std::string>( "ca.l5.expandingdev.Buckey.TTS", "prepareSpeech",sigc::mem_fun( adaptee, &Buckey::TTSService::prepareSpeech ) );
    temp_method->set_arg_name( 0, "words" );
    
    temp_method = this->create_method<void,std::string>( "ca.l5.expandingdev.Buckey.TTS", "selectVoice",sigc::mem_fun( adaptee, &Buckey::TTSService::selectVoice ) );
    temp_method->set_arg_name( 0, "voiceFile" );
    
    temp_method = this->create_method<std::vector<std::string>,uint16_t,uint8_t>( "ca.l5.expandingdev.Buckey.TTS", "getSpeechHistory",sigc::mem_fun( adaptee, &Buckey::TTSService::getSpeechHistory ) );
    temp_method->set_arg_name( 0, "return_value" );
    temp_method->set_arg_name( 1, "index" );
    temp_method->set_arg_name( 2, "range" );
    
    temp_method = this->create_method<std::string>( "ca.l5.expandingdev.Buckey.TTS", "getState",sigc::mem_fun( adaptee, &Buckey::TTSService::getState ) );
    temp_method->set_arg_name( 0, "state" );
    
    speechPreparedSignal = this->create_signal<void, std::string>("ca.l5.expandingdev.Buckey.TTS", "SpeechPrepared");
    speechPreparedSignal->set_arg_name(0, "words");
    
    voiceSwitchedSignal = this->create_signal<void, std::string>("ca.l5.expandingdev.Buckey.TTS", "VoiceSwitched");
    voiceSwitchedSignal->set_arg_name(0, "voiceName");
    
    speechStartedSignal = this->create_signal<void>("ca.l5.expandingdev.Buckey.TTS", "SpeechStarted");
    speechStoppedSignal = this->create_signal<void>("ca.l5.expandingdev.Buckey.TTS", "SpeechStopped");
    
    adaptee->speechStateChangedCallback = std::bind(Buckey::TTSServiceAdapter::signalSpeechStateChanged, this, std::placeholders::_1);
    adaptee->voiceSwitchedCallback = std::bind(Buckey::TTSServiceAdapter::signalVoiceSwitched, this, std::placeholders::_1);
    adaptee->speechPreparedCallback = std::bind(Buckey::TTSServiceAdapter::signalSpeechPrepared, this, std::placeholders::_1);

}

std::shared_ptr<Buckey::TTSServiceAdapter> Buckey::TTSServiceAdapter::create(Buckey::TTSService * adaptee, std::string path ){
    return std::shared_ptr<Buckey::TTSServiceAdapter>( new Buckey::TTSServiceAdapter( adaptee, path ) );

}

void Buckey::TTSServiceAdapter::signalVoiceSwitched(Buckey::TTSServiceAdapter * a, std::string v) {
    a->voiceSwitchedSignal->emit(v);
}

void Buckey::TTSServiceAdapter::signalSpeechStateChanged(Buckey::TTSServiceAdapter * a, bool b) {
    if(b) {
        a->speechStartedSignal->emit();
    }
    else {
        a->speechStoppedSignal->emit();    
    }
}

void Buckey::TTSServiceAdapter::signalSpeechPrepared(Buckey::TTSServiceAdapter * a, std::string w) {
    a->speechPreparedSignal->emit(w);
}
