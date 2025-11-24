
#include "gizmo/log.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

#include <memory>
#include <mutex>
#include <cstdarg>
#include <vector>
#include <string>
#include <cstring>

static std::mutex g_log_mutex;
static std::shared_ptr<spdlog::logger> g_logger = nullptr;
static bool g_initialized = false;

static const char* GIZMO_DEFAULT_PATTERN = "[gizmo] [%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v";

static spdlog::level::level_enum map_level(log_level_t l) {
    switch (l) {
        case LOG_LEVEL_TRACE:    return spdlog::level::trace;
        case LOG_LEVEL_DEBUG:    return spdlog::level::debug;
        case LOG_LEVEL_INFO:     return spdlog::level::info;
        case LOG_LEVEL_WARN:     return spdlog::level::warn;
        case LOG_LEVEL_ERROR:    return spdlog::level::err;
        case LOG_LEVEL_CRITICAL: return spdlog::level::critical;
        case LOG_LEVEL_OFF:      return spdlog::level::off;
        default: return spdlog::level::info;
    }
}

static int create_logger_locked(const char* filename, int initial_level) {
    try {
        std::vector<spdlog::sink_ptr> sinks;
        sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());

        if (filename) {
            auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename, true);
            sinks.push_back(file_sink);
        }

        g_logger = std::make_shared<spdlog::logger>("gizmo_log", sinks.begin(), sinks.end());
        g_logger->set_pattern(GIZMO_DEFAULT_PATTERN);

        if (initial_level >= 0) g_logger->set_level(map_level((log_level_t)initial_level));
        else g_logger->set_level(spdlog::level::info);

        spdlog::register_logger(g_logger);
        spdlog::set_default_logger(g_logger);

        g_initialized = true;
        return 0;
    } catch (...) {
        g_logger = nullptr;
        g_initialized = false;
        return -1;
    }
}

static int ensure_logger_locked() {
    if (g_initialized && g_logger) return 0;
    return create_logger_locked(nullptr, LOG_LEVEL_INFO);
}

static bool vformat_to_string(std::string &out, const char* fmt, va_list ap) {
    if (!fmt) return false;
    int size = 1024;
    std::vector<char> buf(size);
    va_list ap_copy;

    va_copy(ap_copy, ap);
    int needed = vsnprintf(buf.data(), size, fmt, ap_copy);
    va_end(ap_copy);

    if (needed < 0) return false;
    if (needed < size) {
        out.assign(buf.data(), (size_t)needed);
        return true;
    }

    size = needed + 1;
    buf.resize(size);
    
    va_list ap_copy2;
    va_copy(ap_copy2, ap);
    int needed2 = vsnprintf(buf.data(), size, fmt, ap_copy2);
    va_end(ap_copy2);
    
    if (needed2 < 0) return false;
    out.assign(buf.data(), (size_t)needed2);
    return true;
}

extern "C" int log_init(const char* filename) {
    std::lock_guard<std::mutex> lk(g_log_mutex);
    if (g_initialized) {
        try { spdlog::shutdown(); } catch(...) {}
        g_logger = nullptr;
        g_initialized = false;
    }
    return create_logger_locked(filename, LOG_LEVEL_INFO);
}

extern "C" int log_set_level(log_level_t level) {
    std::lock_guard<std::mutex> lk(g_log_mutex);
    if (!g_initialized) {
        if (create_logger_locked(nullptr, LOG_LEVEL_INFO) != 0) return -1;
    }
    try {
        g_logger->set_level(map_level(level));
        return 0;
    } catch (...) {
        return -1;
    }
}

extern "C" int log_print(log_level_t level, const char* fmt, ...) {
    if (!fmt) return -1;
    std::lock_guard<std::mutex> lk(g_log_mutex);

    if (!g_initialized) {
        if (create_logger_locked(nullptr, LOG_LEVEL_INFO) != 0) return -1;
    }

    va_list ap;
    va_start(ap, fmt);
    std::string msg;
    bool ok = vformat_to_string(msg, fmt, ap);
    va_end(ap);
    if (!ok) return -1;

    try {
        auto lvl = map_level(level);
        switch (lvl) {
            case spdlog::level::trace:    g_logger->trace(msg); break;
            case spdlog::level::debug:    g_logger->debug(msg); break;
            case spdlog::level::info:     g_logger->info(msg); break;
            case spdlog::level::warn:     g_logger->warn(msg); break;
            case spdlog::level::err:      g_logger->error(msg); break;
            case spdlog::level::critical: g_logger->critical(msg); break;
            case spdlog::level::off:      /* no-op */ break;
            default: g_logger->info(msg); break;
        }
        return 0;
    } catch (...) {
        return -1;
    }
}

extern "C" void log_shutdown(void) {
    std::lock_guard<std::mutex> lk(g_log_mutex);
    try { spdlog::shutdown(); } catch(...) {}
    g_logger = nullptr;
    g_initialized = false;
}
