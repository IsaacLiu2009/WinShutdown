@echo off
g++.exe src/main.cpp -std=c++20 -O3 -Wall -Wextra -fexec-charset=UTF-8 -Wl,--stack=268435456 -o WinShutdown.exe
pause