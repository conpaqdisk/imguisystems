#include "Memory.h"
#include <TlHelp32.h>
#include <iostream>

namespace Core {
    Memory::Memory(HANDLE hProcess) : m_hProcess(hProcess), m_baseAddress(0) {}

    Memory::~Memory() {}

    uintptr_t Memory::FindPattern(const std::vector<uint8_t>& pattern, const std::string& mask, uintptr_t start, uintptr_t size) {
        if (m_hProcess == NULL) return 0;

        if (size == 0) {
            MODULEENTRY32W modEntry;
            modEntry.dwSize = sizeof(modEntry);
            HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, GetProcessId(m_hProcess));
            if (hSnap != INVALID_HANDLE_VALUE) {
                if (Module32FirstW(hSnap, &modEntry)) {
                    size = modEntry.modBaseSize;
                    start = (uintptr_t)modEntry.modBaseAddr;
                }
                CloseHandle(hSnap);
            }
        }

        if (size == 0) return 0;

        std::vector<uint8_t> buffer(size);
        if (!ReadProcessMemory(m_hProcess, (LPCVOID)start, buffer.data(), size, nullptr))
            return 0;

        size_t patSize = pattern.size();
        if (patSize == 0) return 0;

        for (uintptr_t i = 0; i <= size - patSize; ++i) {
            bool found = true;
            for (size_t j = 0; j < patSize; ++j) {
                if (mask.empty()) {
                    if (buffer[i + j] != pattern[j]) { found = false; break; }
                } else {
                    if (mask[j] != '?' && buffer[i + j] != pattern[j]) { found = false; break; }
                }
            }
            if (found) return start + i;
        }
        return 0;
    }

    DWORD Memory::GetProcId(const std::wstring& procName) {
        DWORD procId = 0;
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnap != INVALID_HANDLE_VALUE) {
            PROCESSENTRY32W procEntry;
            procEntry.dwSize = sizeof(procEntry);
            if (Process32FirstW(hSnap, &procEntry)) {
                do {
                    if (!_wcsicmp(procEntry.szExeFile, procName.c_str())) {
                        procId = procEntry.th32ProcessID;
                        break;
                    }
                } while (Process32NextW(hSnap, &procEntry));
            }
        }
        CloseHandle(hSnap);
        return procId;
    }

    uintptr_t Memory::GetModuleBaseAddress(DWORD procId, const std::wstring& modName) {
        uintptr_t modBaseAddr = 0;
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
        if (hSnap != INVALID_HANDLE_VALUE) {
            MODULEENTRY32W modEntry;
            modEntry.dwSize = sizeof(modEntry);
            if (Module32FirstW(hSnap, &modEntry)) {
                do {
                    if (!_wcsicmp(modEntry.szModule, modName.c_str())) {
                        modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                        break;
                    }
                } while (Module32NextW(hSnap, &modEntry));
            }
        }
        CloseHandle(hSnap);
        return modBaseAddr;
    }
}
