#pragma once
#include <Windows.h>
#include <vector>
#include <cstdint>
#include <string>

namespace Core {
    class Memory {
    public:
        Memory(HANDLE hProcess);
        ~Memory();

        template <typename T>
        bool Read(uintptr_t address, T& out) const {
            if (!m_hProcess) return false;
            return ReadProcessMemory(m_hProcess, (LPCVOID)address, &out, sizeof(T), nullptr);
        }

        template <typename T>
        bool Write(uintptr_t address, const T& value) const {
            if (!m_hProcess) return false;
            return WriteProcessMemory(m_hProcess, (LPVOID)address, &value, sizeof(T), nullptr);
        }

        uintptr_t FindPattern(const std::vector<uint8_t>& pattern, const std::string& mask = "", uintptr_t start = 0, uintptr_t size = 0);

        uintptr_t GetBaseAddress() const { return m_baseAddress; }
        void SetBaseAddress(uintptr_t base) { m_baseAddress = base; }
        HANDLE GetHandle() const { return m_hProcess; }

        static DWORD GetProcId(const std::wstring& procName);
        static uintptr_t GetModuleBaseAddress(DWORD procId, const std::wstring& modName);

    private:
        HANDLE m_hProcess;
        uintptr_t m_baseAddress;
    };
}
