#ifndef TTSSERVICEPROXY_H
#define TTSSERVICEPROXY_H

#include <dbus-cxx.h>
#include <memory>
#include <stdint.h>
#include <string>
#include "ServiceProxy.h"

namespace Buckey {

class TTSServiceProxy : public Buckey::ServiceProxy {
	protected:
		TTSServiceProxy(DBus::Connection::pointer conn, std::string dest, std::string path);	
	public:
        static std::shared_ptr<Buckey::TTSServiceProxy> create(DBus::Connection::pointer conn, std::string dest, std::string path);
    	void speak(std::string words);
        void prepareSpeech(std::string words);
        void selectVoice(std::string voiceFile);
        std::vector<std::string> getSpeechHistory(uint16_t index, uint8_t range);
        std::string getState();

    protected:
        DBus::MethodProxy<void,std::string>::pointer  m_method_speak;
        DBus::MethodProxy<void,std::string>::pointer  m_method_prepareSpeech;
        DBus::MethodProxy<void,std::string>::pointer  m_method_selectVoice;
        DBus::MethodProxy<std::vector<std::string>,uint16_t,uint8_t>::pointer  m_method_getSpeechHistory;
        DBus::MethodProxy<std::string>::pointer  m_method_getState;

};

}
#endif /* TTSSERVICEPROXY_H */
