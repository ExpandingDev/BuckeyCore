#include "ASRServiceProxy.h"

namespace Buckey {
    ASRServiceProxy::ASRServiceProxy(DBus::Connection::pointer conn, std::string dest, std::string path) : ServiceProxy(conn, dest, path){
        m_method_setListeningBehavior = this->create_method<void,uint8_t>("ca.l5.expandingdev.Buckey.ASR","setListeningBehavior");
        m_method_setGrammar = this->create_method<void,std::string>("ca.l5.expandingdev.Buckey.ASR","setGrammar");
        m_method_setLanguageModel = this->create_method<void,std::string>("ca.l5.expandingdev.Buckey.ASR","setLanguageModel");
        m_method_setKeyword = this->create_method<void,std::string>("ca.l5.expandingdev.Buckey.ASR","setKeyword");
        m_method_setRecognitionMode = this->create_method<void,uint8_t>("ca.l5.expandingdev.Buckey.ASR","setRecognitionMode");
        m_method_startListening = this->create_method<void>("ca.l5.expandingdev.Buckey.ASR","startListening");
        m_method_stopListening = this->create_method<void>("ca.l5.expandingdev.Buckey.ASR","stopListening");
    
    }
    
    std::shared_ptr<ASRServiceProxy> ASRServiceProxy::create(DBus::Connection::pointer conn, std::string dest, std::string path) {
        return std::shared_ptr<ASRServiceProxy>(new ASRServiceProxy(conn, dest, path));
    }
    
    void ASRServiceProxy::setListeningBehavior(uint8_t type){
        (*m_method_setListeningBehavior)(type);
    }
    
    void ASRServiceProxy::setGrammar(std::string jsgf){
        (*m_method_setGrammar)(jsgf); 
    }
    
    void ASRServiceProxy::setLanguageModel(std::string lmpath){
        (*m_method_setLanguageModel)(lmpath);    
    }
    
    void ASRServiceProxy::setKeyword(std::string keyword){
        (*m_method_setKeyword)(keyword);
    }
    
    void ASRServiceProxy::setRecognitionMode(uint8_t mode){
        (*m_method_setRecognitionMode)(mode);
    }
    
    void ASRServiceProxy::startListening(){
        (*m_method_startListening)();
    }
    
    void ASRServiceProxy::stopListening(){
        (*m_method_stopListening)();
    }
}