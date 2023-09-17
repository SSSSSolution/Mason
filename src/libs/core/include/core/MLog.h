#ifndef MASON_MLOG_H
#define MASON_MLOG_H

#include <string>
#include <map>

#include <win-export/WinExport.h>

#define MTrace(message) mason::MLog::log(mason::MLog::Level::Trace, "", message, __FILE__, __LINE__)
#define MDebug(message) mason::MLog::log(mason::MLog::Level::Debug, "", message, __FILE__, __LINE__)
#define MInfo(message) mason::MLog::log(mason::MLog::Level::Info, "", message, __FILE__, __LINE__)
#define MWarning(message) mason::MLog::log(mason::MLog::Level::Warning, "", message, __FILE__, __LINE__)
#define MError(message) mason::MLog::log(mason::MLog::Level::Error, "", message, __FILE__, __LINE__)
#define MFatal(message) mason::MLog::log(mason::MLog::Level::Fatal, "", message, __FILE__, __LINE__)

#define MMTrace(module, message) mason::MLog::log(mason::MLog::Level::Trace, module, message, __FILE__, __LINE__)
#define MMDebug(module, message) mason::MLog::log(mason::MLog::Level::Debug, module, message, __FILE__, __LINE__)
#define MMInfo(module, message) mason::MLog::log(mason::MLog::Level::Info, module, message, __FILE__, __LINE__)
#define MMWarning(module, message) mason::MLog::log(mason::MLog::Level::Warning, module, message, __FILE__, __LINE__)
#define MMError(module, message) mason::MLog::log(mason::MLog::Level::Error, module, message, __FILE__, __LINE__)
#define MMFatal(module, message) mason::MLog::log(mason::MLog::Level::Fatal, module, message, __FILE__, __LINE__)

namespace mason {

class MASON_CORE_API MLog {
public:
    enum class Level {
        Trace,
        Debug,
        Info,
        Warning,
        Error,
        Fatal
    };

    static void log(Level level, const std::string &module, const std::string &message, const std::string &file, int line);

private:
    static void initialize(const std::string &file_path);
    static void set_log_level(Level level, const std::string &module = "");
    // todo: add set_log_flush_level() to flush logs at a certain level

private:
    static std::string s_log_path;
    static std::map<std::string, Level> s_log_levels;
    static const Level DEFAULT_LOG_LEVEL = Level::Info;

    friend class MApp;
};

}

#endif
