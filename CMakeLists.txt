cmake_minimum_required(VERSION 3.5)

project(KoiFish)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(ARDUINO_LIB_DIR "$ENV{USERPROFILE}\\Documents\\Arduino\\libraries")
message(STATUS "Arduino Library Directory: ${ARDUINO_LIB_DIR}")
set(ARDUINO_15_DIR "$ENV{LOCALAPPDATA}\\Arduino15")
message(STATUS "Arduino15 Directory: ${ARDUINO_15_DIR}")

include_directories(
    "${ARDUINO_15_DIR}\\packages\\esp8266\\hardware\\esp8266\\3.1.2\\cores\\esp8266"
    "${ARDUINO_15_DIR}\\packages\\esp8266\\hardware\\esp8266\\3.1.2\\libraries\\ESP8266WiFi\\src"
    "${ARDUINO_15_DIR}\\packages\\esp8266\\hardware\\esp8266\\3.1.2\\libraries\\Servo\\src"
    "${PROJECT_SOURCE_DIR}\\include\\NTPClientNeovim"
    "${ARDUINO_LIB_DIR}\\LiquidCrystal_I2C"
    "${ARDUINO_LIB_DIR}\\PubSubClient\\src"
    )

add_executable(
    main

    src/main.cpp
    src/program.cpp
    src/timer.cpp
    src/reminder.cpp
    src/ui.cpp
    src/servo.cpp
    src/netpie.cpp
    src/mqtt.cpp
    src/feeder.cpp
    )
