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

	class NTPTimer : private NTPClient {
		public:
			NTPTimer(WiFiUDP& udp, const char* pool, long off); 
			~NTPTimer() = default;

		public:
			String time(Unit unit);
			void print(Unit unit);
	};
};
