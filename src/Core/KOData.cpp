#include "KOData.h"
#include "Memory.h"
#include "Logger.h"

namespace KOData {
    const std::vector<uint8_t> PATTERN_CHR = { 0xA1, 0x00, 0x00, 0x00, 0x00, 0x85, 0xC0, 0x74, 0x00 };
    const std::vector<uint8_t> PATTERN_FLDB = { 0x00 }; 
    const std::vector<uint8_t> PATTERN_DLG = { 0x00 };
    const std::vector<uint8_t> PATTERN_PKT = { 0x00 };
    const std::vector<uint8_t> PATTERN_GAMEPROCMAIN = { 0x00 };
    const std::vector<uint8_t> PATTERN_SEND = { 0x00 };
    const std::vector<uint8_t> PATTERN_RECV = { 0x00 };

    uintptr_t g_baseAddress = 0;
    uintptr_t g_chrPtr = 0;
    uintptr_t g_fldbPtr = 0;
    uintptr_t g_dlgPtr = 0;
    uintptr_t g_pktPtr = 0;
    uintptr_t g_gameProcMain = 0;
    uintptr_t g_sendFunc = 0;
    uintptr_t g_recvFunc = 0;

    bool Initialize(uintptr_t baseAddress, Core::Memory& mem) {
        g_baseAddress = baseAddress;

        // g_chrPtr = mem.FindPattern(PATTERN_CHR, "xxxxxxx?x");
        // if (!g_chrPtr) {
        //    LOG_ERROR("CHR pointer could not be found!");
        //    return false;
        // }
        
        return true;
    }
}
