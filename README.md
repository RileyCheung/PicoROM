# PicoROM

PicoROM is a cost-effective alternative to traditional EEPROM solutions for Ben Eater's 6502 Breadboard Computer project. Instead of using expensive 28C256 32K EEPROM chips and dedicated EEPROM programmers, this project implements a ROM emulator using a Raspberry Pi Pico and level shifters.

Features
* Fully emulates a 32K ROM (28C256 compatible)
* Simple level-shifting circuitry for interfacing the 3.3v Pico with the 5v 6502
* Easy programming via USB connection
* Compatible with standard ROM images (.bin files)
* Address and Data bus signal serial port reading
