#include "Logger.h"

namespace Core {
    std::string Logger::s_filename = "KOTracker.log";
    std::mutex Logger::s_mutex;
}
