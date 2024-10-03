/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#include "Logging.h"
#include "Terminal.h"
#include <chrono>
#include <iostream>
#include <iomanip>

std::string get_current_time() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
    localtime_r(&time, &tm);  // Thread-safe on POSIX systems

    std::stringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::string get_log_level_string(AK::LogLevel level) {
    switch (level) {
        case AK::DEBUG: return "DEBUG";
        case AK::INFO: return "INFO";
        case AK::WARN: return "WARNING";
        case AK::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

std::string get_level_color(AK::LogLevel level) {
    switch(level) {
        case AK::DEBUG: return AK::BLUE;
        case AK::INFO: return AK::GREEN;
        case AK::WARN: return AK::YELLOW;
        case AK::ERROR: return AK::RED;
        default: return AK::RESET;
    }
}

void log_message(const std::string& message, AK::LogLevel level) {
    const std::string color = get_level_color(level);
    const std::string level_str = get_log_level_string(level);
    std::cout << color << "[" << get_current_time() << "] [" << level_str << "] " << AK::RESET << message << std::endl;
}

void AK::error(const std::string & message) {
    log_message(message, ERROR);
}

void AK::info(const std::string & message) {
    log_message(message, INFO);
}

void AK::warn(const std::string & message) {
    log_message(message, WARN);
}

void AK::debug(const std::string & message) {
    log_message(message, DEBUG);
}
