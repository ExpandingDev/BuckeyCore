#include "UIO.h"

namespace Buckey {
	void UIO::log(std::string message) {
		logSignal->emit(message);
	}

	void UIO::warning(std::string message) {
		warningSignal->emit(message);
	}

	void UIO::warn(std::string message) {
		warningSignal->emit(message);
	}

	void UIO::error(std::string message) {
		errorSignal->emit(message);
	}

	void UIO::speak(std::string words) {
		speakSignal->emit(words);
	}

	void UIO::notification(std::string title, std::string message, int id) {
		notificationSignal->emit(title, message, id);
	}

	void UIO::alarm(std::string title, std::string message, int id) {
		alarmSignal->emit(title, message, id);
	}

	UIO::UIO(std::shared_ptr<DBus::Object> source) {
		sourceObject = source;
		logSignal = source->create_signal<void, std::string>("ca.l5.expandingdev.Buckey.UIO", "Log");
		warningSignal = source->create_signal<void, std::string>("ca.l5.expandingdev.Buckey.UIO", "Warning");
		errorSignal = source->create_signal<void, std::string>("ca.l5.expandingdev.Buckey.UIO", "Error");
		speakSignal = source->create_signal<void, std::string>("ca.l5.expandingdev.Buckey.UIO", "Speaking");
		notificationSignal = source->create_signal<void, std::string, std::string, int>("ca.l5.expandingdev.Buckey.UIO", "Notification");
		alarmSignal = source->create_signal<void, std::string, std::string, int>("ca.l5.expandingdev.Buckey.UIO", "Alarm");
	}

	UIO::~UIO() {

	}
}
