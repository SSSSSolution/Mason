#include "core/MLog.h"

#include <filesystem>
#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace mason {

std::string MLog::s_log_path = "";
std::map <std::string, MLog::Level> MLog::s_log_levels = {};
std::shared_ptr<spdlog::logger> s_logger = nullptr;

void MLog::initialize(const std::string &file_path) {
    // todo: check spdlog error
    s_log_path = file_path;
    s_logger = spdlog::basic_logger_mt("Mason", s_log_path);
    spdlog::set_default_logger(s_logger);
    spdlog::set_level(spdlog::level::trace);
    spdlog::set_pattern("[%l][%Y-%m-%d %H:%M:%S.%e] %v");
}

void MLog::set_log_level(Level level, const std::string &module) {
    s_log_levels[module] = level;
}

void MLog::log(mason::MLog::Level level,
               const std::string &module,
               const std::string &message,
               const std::string &file,
               int line) {
    // todo: check if disk is full

    if (s_logger == nullptr) {
        std::cout << "MLog::log() called before MLog::initialize()" << std::endl;
        // todo: add to queue and log after initialization
        return;
    }
    
    auto found_level = s_log_levels.find(module);

    if (found_level != s_log_levels.end()) {
        if (found_level->second > level) {
            return;
        }
    } else {
        auto global_level_it = s_log_levels.find("");
        if (global_level_it != s_log_levels.end() && global_level_it->second > level) {
            return;
        } else if (DEFAULT_LOG_LEVEL > level) {
            return;
        }
    }

    std::string filename = std::filesystem::path(file).filename().string();

    auto logMessage = [&](auto logFunc, bool log_file_line = true) {
        if (module.empty()) {
            log_file_line ? logFunc("[{}:{}] {}", filename, line, message) :
                            logFunc(message);
        } else {
            log_file_line ? logFunc("[{}:{}][{}] {}", filename, line, module, message) :
                            logFunc("[{}] {}", module, message);
        }
    };

    switch (level) {
        case Level::Trace: logMessage([&](auto... args) { s_logger->trace(args...); }, false); break;
        case Level::Debug: logMessage([&](auto... args) { s_logger->debug(args...); }, false); break;
        case Level::Info: logMessage([&](auto... args) { s_logger->info(args...); }, false); break;
        case Level::Warning: logMessage([&](auto... args) { s_logger->warn(args...); }); break;
        case Level::Error: logMessage([&](auto... args) { s_logger->error(args...); }); break;
        case Level::Fatal: logMessage([&](auto... args) { s_logger->critical(args...); }); break;
    }

    s_logger->flush();
}

}
