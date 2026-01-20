# EnvironSense
A compact Arduino-based environmental monitor that measures temperature, humidity, pressure, and air quality using a BME680 sensor and displays real-time data on a monochrome OLED with a low-memory embedded UI.

This project is a compact environmental monitoring system built using an Arduino Nano, a BME680 sensor, and a 128×64 monochrome OLED display. It measures and displays real-time temperature (°C/°F), relative humidity, air pressure, and an air quality proxy based on gas resistance.

The system is designed with embedded constraints in mind:

  - Uses I²C for efficient sensor and display communication

  - Optimized for low SRAM usage with the U8x8 text-based OLED interface

  - Implements clear, flicker-free UI updates and status indicators

  - Interprets raw sensor data into meaningful environmental states (e.g. humidity and air quality levels)

A hands-on project that pulls data from a BME680 and shows it on an OLED, focused on learning sensor integration, embedded UI design, and building firmware that operate within hardware limits.
