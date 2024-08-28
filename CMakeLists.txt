cmake_minimum_required(VERSION 3.0)

project(KoiFish)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
    "C:/Users/tytgsjsn/.platformio/packages/toolchain-xtensa/xtensa-lx106-elf/include"
    "C:/Users/tytgsjsn/.platformio/packages/framework-arduinoespressif8266/tools/sdk/include"
    "C:/Users/tytgsjsn/.platformio/packages/framework-arduinoespressif8266/cores/esp8266"
    "C:/Users/tytgsjsn/.platformio/packages/framework-arduinoespressif8266/libraries/ESP8266WiFi/src"
    "C:/Users/tytgsjsn/.platformio/packages/framework-arduinoespressif8266/libraries/NTPClient/src"
    "C:/Users/tytgsjsn/.platformio/packages/framework-arduinoespressif8266/libraries/LiquidCrystal_I2C/src"
    "C:/Users/tytgsjsn/.platformio/packages/framework-arduinoespressif8266/libraries/Servo/src"
    )

add_executable(
    main

    src/main.cpp
    src/program.cpp
    src/timer.cpp
    src/reminder.cpp
    src/ui.cpp
    src/servo.hpp
    src/servo.cpp
    )
