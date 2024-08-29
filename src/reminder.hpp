#include "type.hpp"
#include "timer.hpp"

#include <Arduino.h>

namespace Time {
	class Reminder {
		private:
			NTPTimer* timer;
			String* remind;
			u16 max_remind;
			Unit time_unit;

		public:
			Reminder(NTPTimer* timer, u16 remind_count, Unit time_unit); 
			~Reminder();

		public:
			u8 add(const String& time);
			u8 del(const String& time);
			bool check();

		private:
			bool is_dupe_remind(const String& time);
			i32 find_remind(const String& time);
	};
};
