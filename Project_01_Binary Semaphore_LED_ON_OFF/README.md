# Project 01: FreeRTOS Binary Semaphore – LED ON_OFF

## 1. Overview
Control an LED using a push button with FreeRTOS Binary Semaphore for task synchronization.

## 2. Hardware
- ESP32-S3 DevKitC-1
- LED – GPIO 5
- Push Button – GPIO 12

## 3. How It Works
1. Button Task detects a button press.
2. Binary Semaphore sends an event signal.
3. LED Task receives the signal.
4. LED changes its ON/OFF state.

## 4. FreeRTOS Concepts
- Task Creation
- Task Synchronization
- Binary Semaphore
- Semaphore Take / Give

## 5. Development Tools
- ESP-IDF
- FreeRTOS
- Wokwi Simulator