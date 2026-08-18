#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <mutex>

namespace Core {
    class Logger {
    public:
        static void Init(const std::string& filename) {
            s_filename = filename;
        }

        static void Log(const std::string& msg) {
            std::lock_guard<std::mutex> lock(s_mutex);
            std::ofstream file(s_filename, std::ios::app);
            if (file.is_open()) {
                file << msg << std::endl;
            }
            std::cout << msg << std::endl;
        }

        template <typename T>
        static void Log(const T& msg) {
            Log(std::to_string(msg));
        }

        static void Error(const std::string& msg) {
            Log("[HATA] " + msg);
        }

    private:
        static std::string s_filename;
        static std::mutex s_mutex;
    };
}

#define LOG(msg) Core::Logger::Log(msg)
#define LOG_ERROR(msg) Core::Logger::Error(msg)
