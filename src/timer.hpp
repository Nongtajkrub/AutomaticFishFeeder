#pragma once

#include "type.hpp"
#include <NTPClient.h>

enum class TimeUnit : u8 {
    HOUR,
    MINUTE,
    SECOND
};

class NTPTimer : private NTPClient {
    public:
	NTPTimer(WiFiUDP& udp, const char* pool, long off); 
	~NTPTimer() = default;

    public:
	String time(TimeUnit unit);
	void print(TimeUnit unit);
};

