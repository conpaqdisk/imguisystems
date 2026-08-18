#include "PipeClient.h"
#include <iostream>
#include <vector>
#include <sstream>

namespace Core
{
    PipeClient::PipeClient() : m_running(false), m_connected(false), m_hPipe(INVALID_HANDLE_VALUE)
    {
    }

    PipeClient::~PipeClient()
    {
        Stop();
    }

    void PipeClient::Start()
    {
        if (m_running) return;
        m_running = true;
        m_thread = std::thread(&PipeClient::ConnectThread, this);
        m_pollThread = std::thread(&PipeClient::PollThread, this);
    }

    void PipeClient::Stop()
    {
        m_running = false;
        if (m_hPipe != INVALID_HANDLE_VALUE)
        {
            CloseHandle(m_hPipe);
            m_hPipe = INVALID_HANDLE_VALUE;
        }
        if (m_thread.joinable()) m_thread.join();
        if (m_pollThread.joinable()) m_pollThread.join();
    }

    std::string PipeClient::SendCommand(const std::string& cmd)
    {
        std::lock_guard<std::mutex> lock(m_pipeMutex);
        if (!m_connected || m_hPipe == INVALID_HANDLE_VALUE) return "";

        DWORD bytesWritten;
        if (!WriteFile(m_hPipe, cmd.c_str(), (DWORD)cmd.length(), &bytesWritten, NULL))
        {
            m_connected = false;
            return "";
        }

        char buffer[1024] = {0};
        DWORD bytesRead;
        if (!ReadFile(m_hPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL))
        {
            m_connected = false;
            return "";
        }

        return std::string(buffer, bytesRead);
    }

    void PipeClient::SendLootPacket(uint32_t bundleId, uint32_t itemId)
    {
        if (!AppState::Get().General.autoLoot) return;

        // 1. Send WIZ_BUNDLE_OPEN_REQ (0x24)
        std::stringstream reqStream;
        reqStream << "PKT_SEND:24" << std::hex << bundleId; 
        std::string reqCmd = reqStream.str();
        SendCommand(reqCmd);

        // 2. Wait slightly for server response, then send WIZ_ITEM_GET (0x26)
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        std::stringstream getStream;
        getStream << "PKT_SEND:26" << std::hex << bundleId;
        
        if (itemId == 0) // Noah
            getStream << "00" << "E9A4350000"; // Fake hardcoded representation for demonstration
        else
            getStream << "50" << "FF4D300100"; // Fake hardcoded representation for demonstration
            
        std::string getCmd = getStream.str();
        SendCommand(getCmd);
    }

    void PipeClient::ConnectThread()
    {
        while (m_running)
        {
            if (!m_connected)
            {
                m_pipeMutex.lock();
                if (m_hPipe != INVALID_HANDLE_VALUE)
                {
                    CloseHandle(m_hPipe);
                    m_hPipe = INVALID_HANDLE_VALUE;
                }

                if (WaitNamedPipeA("\\\\.\\pipe\\TecHKaySPipe", 1000))
                {
                    m_hPipe = CreateFileA(
                        "\\\\.\\pipe\\TecHKaySPipe",
                        GENERIC_READ | GENERIC_WRITE,
                        0,
                        NULL,
                        OPEN_EXISTING,
                        0,
                        NULL
                    );

                    if (m_hPipe != INVALID_HANDLE_VALUE)
                    {
                        DWORD mode = PIPE_READMODE_MESSAGE;
                        SetNamedPipeHandleState(m_hPipe, &mode, NULL, NULL);
                        m_connected = true;
                    }
                }
                m_pipeMutex.unlock();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

    // Helper for splitting strings
    static std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> result;
        std::stringstream ss(s);
        std::string item;
        while (getline(ss, item, delim)) {
            result.push_back(item);
        }
        return result;
    }

    void PipeClient::PollThread()
    {
        while (m_running)
        {
            if (m_connected)
            {
                std::string resp = SendCommand("CHARINFO");
                if (resp.find("CHARINFO:") == 0 && resp != "CHARINFO:OFFLINE")
                {
                    // Parse CHARINFO:Name|LV=99|CL=108|HP=100/100|MP=100/100|X=123|Y=456
                    std::string data = resp.substr(9);
                    auto parts = split(data, '|');
                    
                    auto& state = AppState::Get();
                    if (!parts.empty())
                    {
                        state.CharacterName = parts[0];
                        
                        for (size_t i = 1; i < parts.size(); ++i)
                        {
                            auto kv = split(parts[i], '=');
                            if (kv.size() == 2)
                            {
                                if (kv[0] == "LV") state.Level = std::stoi(kv[1]);
                                else if (kv[0] == "CL") state.General.selectedClassId = std::stoi(kv[1]);
                                else if (kv[0] == "HP") {
                                    auto hpVals = split(kv[1], '/');
                                    if (hpVals.size() == 2) {
                                        state.CurrentHP = std::stoi(hpVals[0]);
                                        state.MaxHP = std::stoi(hpVals[1]);
                                    }
                                }
                                else if (kv[0] == "MP") {
                                    auto mpVals = split(kv[1], '/');
                                    if (mpVals.size() == 2) {
                                        state.CurrentMP = std::stoi(mpVals[0]);
                                        state.MaxMP = std::stoi(mpVals[1]);
                                    }
                                }
                                else if (kv[0] == "X") state.PosX = std::stof(kv[1]);
                                else if (kv[0] == "Y") state.PosY = std::stof(kv[1]);
                            }
                        }
                        state.CurrentStatus = AppStatus::Running;
                    }
                }
                else if (resp == "CHARINFO:OFFLINE")
                {
                    AppState::Get().CurrentStatus = AppStatus::Ready;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
}
