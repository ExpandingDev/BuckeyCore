#include "ASRService.h"

namespace Buckey {
    ASRService::RecognitionMode ASRService::recognitionModeFromByte(uint8_t m) {
        switch(m) {
            case 0:
                return ASRService::RecognitionMode::JSGF;
                break;
            case 1:
                return ASRService::RecognitionMode::LANGUAGE_MODEL;
                break;
            default:
                return ASRService::RecognitionMode::JSGF;
                break;      
        }    
    }
    
    uint8_t ASRService::byteFromRecognitionMode(ASRService::RecognitionMode l) {
        if(l == ASRService::RecognitionMode::JSGF) {
            return 0;
        }
        else if(l == ASRService::RecognitionMode::LANGUAGE_MODEL) {
            return 1;        
        }
        
        return 0;
    }
    
    ASRService::ListeningMode ASRService::listeningModeFromByte(uint8_t m) {
        switch(m) {
            case 0:
                return ASRService::ListeningMode::CONTINUOUS;
                break;
            case 1:
                return ASRService::ListeningMode::PUSH_TO_SPEAK;
                break;
            case 2:
                return ASRService::ListeningMode::FILE;
                break;
            case 3:
                return ASRService::ListeningMode::STREAM;
                break;     
            default:
                return ASRService::ListeningMode::CONTINUOUS;
                break;   
        }
    }
    
    uint8_t ASRService::byteFromListeningMode(ASRService::ListeningMode l) {
        if(l == ASRService::ListeningMode::CONTINUOUS) {
            return 0;        
        }
        else if(l == ASRService::ListeningMode::PUSH_TO_SPEAK) {
            return 1;
        }
        else if(l == ASRService::ListeningMode::FILE) {
            return 2;
        }
        else if(l == ASRService::ListeningMode::STREAM) {
            return 3;
        }
        return 0;
    }
    
    void ASRService::_setRecognitionMode(uint8_t mode) {
        setRecognitionMode(recognitionModeFromByte(mode));    
    }
    
    void ASRService::_setListeningBehavior(uint8_t mode) {
        setListeningBehavior(listeningModeFromByte(mode));    
    }
}