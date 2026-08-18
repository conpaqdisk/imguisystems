#pragma once
#include <string>
#include <windows.h>
#include <thread>
#include <atomic>
#include <mutex>
#include "AppState.h"

namespace Core
{
    class PipeClient
    {
    public:
        static PipeClient& Get()
        {
            static PipeClient instance;
            return instance;
        }

        void Start();
        void Stop();
        
        bool IsConnected() const { return m_connected; }
        std::string SendCommand(const std::string& cmd);
        void SendLootPacket(uint32_t bundleId, uint32_t itemId);

    private:
        PipeClient();
        ~PipeClient();
        
        void ConnectThread();
        void PollThread();
        
        std::atomic<bool> m_running;
        std::atomic<bool> m_connected;
        HANDLE m_hPipe;
        std::thread m_thread;
        std::thread m_pollThread;
        std::mutex m_pipeMutex;
    };
}
