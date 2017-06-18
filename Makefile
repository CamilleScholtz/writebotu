BOARDS_TXT = ${ARDUINO_DIR}/hardware/arduino/avr/boards.txt
BOARD_TAG  = mega
BOARD_SUB  = atmega2560

DEBUG_FLAGS = -g -O0 -DDEBUG

include /usr/share/arduino/Arduino.mk
