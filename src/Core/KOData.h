#pragma once
#include <cstdint>
#include <vector>
#include <string>

namespace KOData {
    extern const std::vector<uint8_t> PATTERN_CHR;
    extern const std::vector<uint8_t> PATTERN_FLDB;
    extern const std::vector<uint8_t> PATTERN_DLG;
    extern const std::vector<uint8_t> PATTERN_PKT;
    extern const std::vector<uint8_t> PATTERN_GAMEPROCMAIN;
    extern const std::vector<uint8_t> PATTERN_SEND;
    extern const std::vector<uint8_t> PATTERN_RECV;

    constexpr uintptr_t OFF_NAME      = 0x6A4;
    constexpr uintptr_t OFF_HP        = 0x6D8;
    constexpr uintptr_t OFF_MAX_HP    = 0x6D4;
    constexpr uintptr_t OFF_POSX      = 0x3CC;
    constexpr uintptr_t OFF_POSY      = 0x3D4;
    constexpr uintptr_t OFF_POSZ      = 0x194;
    constexpr uintptr_t OFF_ID        = 0x6A0;
    constexpr uintptr_t OFF_MOVE      = 0x1014;
    constexpr uintptr_t OFF_MOUSE_X   = 0x1020;
    constexpr uintptr_t OFF_MOUSE_Y   = 0x1028;
    constexpr uintptr_t OFF_LEVEL     = 0x6D0;
    constexpr uintptr_t OFF_CLASS     = 0x6CC;
    constexpr uintptr_t OFF_MP        = 0xBF0;
    constexpr uintptr_t OFF_MAX_MP    = 0xBEC;
    constexpr uintptr_t OFF_TARGET    = 0x660;
    constexpr uintptr_t OFF_NATION    = 0x6C4;

    extern uintptr_t g_baseAddress;
    extern uintptr_t g_chrPtr;
    extern uintptr_t g_fldbPtr;
    extern uintptr_t g_dlgPtr;
    extern uintptr_t g_pktPtr;
    extern uintptr_t g_gameProcMain;
    extern uintptr_t g_sendFunc;
    extern uintptr_t g_recvFunc;
}
