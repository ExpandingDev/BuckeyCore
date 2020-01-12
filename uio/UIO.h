#include <string>
#include <memory>
#include "dbus-cxx.h"

namespace Buckey {
	class UIO {
		public:
			void log(std::string message);
			void warning(std::string message);
			void warn(std::string message);
			void error(std::string message);

			void speak(std::string message);
			void notification(std::string title, std::string message, int id=-1);
			void alarm(std::string title, std::string message, int id=-1);

			UIO(std::shared_ptr<DBus::Object> source);
			virtual ~UIO();

		protected:
			std::shared_ptr<DBus::Object> sourceObject;

		private:
			DBus::signal<void, std::string>::pointer logSignal;
			DBus::signal<void, std::string>::pointer warningSignal;
			DBus::signal<void, std::string>::pointer errorSignal;
			DBus::signal<void, std::string>::pointer speakSignal;
			DBus::signal<void, std::string, std::string, int>::pointer notificationSignal;
			DBus::signal<void, std::string, std::string, int>::pointer alarmSignal;
	};
}
