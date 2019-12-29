#include "TTSServiceProxy.h"

Buckey::TTSServiceProxy::TTSServiceProxy(DBus::Connection::pointer conn, std::string dest, std::string path ) : Buckey::ServiceProxy(conn, dest, path){
    m_method_speak = this->create_method<void,std::string>("ca.l5.expandingdev.Buckey.TTS","speak");
    m_method_prepareSpeech = this->create_method<void,std::string>("ca.l5.expandingdev.Buckey.TTS","prepareSpeech");
    m_method_selectVoice = this->create_method<void,std::string>("ca.l5.expandingdev.Buckey.TTS","selectVoice");
    m_method_getSpeechHistory = this->create_method<std::vector<std::string>,uint16_t,uint8_t>("ca.l5.expandingdev.Buckey.TTS","getSpeechHistory");
    m_method_getState = this->create_method<std::string>("ca.l5.expandingdev.Buckey.TTS","getState");

}

std::shared_ptr<Buckey::TTSServiceProxy> Buckey::TTSServiceProxy::create(DBus::Connection::pointer conn, std::string dest, std::string path){
    return std::shared_ptr<Buckey::TTSServiceProxy>(new Buckey::TTSServiceProxy(conn, dest, path ));
}

void Buckey::TTSServiceProxy::speak(std::string words) {
    (*m_method_speak)(words);
}

void Buckey::TTSServiceProxy::prepareSpeech(std::string words) {
    (*m_method_prepareSpeech)(words);
}

void Buckey::TTSServiceProxy::selectVoice(std::string voiceFile) {
    (*m_method_selectVoice)(voiceFile);
}

std::vector<std::string> Buckey::TTSServiceProxy::getSpeechHistory(uint16_t index, uint8_t range ){
    return (*m_method_getSpeechHistory)(index,range);
}

std::string Buckey::TTSServiceProxy::getState( ){
    return (*m_method_getState)();
}
