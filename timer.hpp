#pragma once

#include "type.hpp"

#include <NTPClient.h>
#include <WiFiUdp.h>

namespace Time {
	enum class Unit : u8 {
		HOUR,
		MINUTE,
		SECOND
	};

	class Timer : private NTPClient {
		public:
			Timer(WiFiUDP& udp, const char* pool, long offset); 
			~Timer() = default;

		public:
			String string_time(Unit unit);
			void print(Unit unit);
	};
};
