#pragma once

#include <time.h>
#include <iostream>
#include <cstdarg>
#include <termcolor/termcolor.hpp>

enum LogLevel {
    INFO = 1, WARN, ERROR
};

static void Log(LogLevel logLevel, const char* format, ...)
{
    time_t t = time(0);
    struct tm* now = localtime(&t);
    switch(logLevel) {
    case INFO:
        printf("[%02d:%02d:%02d]  INFO : ", now->tm_hour, now->tm_min, now->tm_sec);
        break;
    case WARN:
        std::cout << termcolor::yellow;
        printf("[%02d:%02d:%02d]  WARN : ", now->tm_hour, now->tm_min, now->tm_sec);
        break;
    case ERROR:
        std::cout << termcolor::red;
        printf("[%02d:%02d:%02d] ERROR : ", now->tm_hour, now->tm_min, now->tm_sec);
        break;
    }
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    std::cout << std::endl << termcolor::white;
}
