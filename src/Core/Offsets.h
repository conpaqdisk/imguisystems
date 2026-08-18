#pragma once

namespace Core
{
    namespace Offsets
    {
        constexpr unsigned int KO_PTR_CHR = 0x01115834;
        constexpr unsigned int KO_PTR_DLG = 0x011158FC;
        constexpr unsigned int KO_PTR_PKT = 0x01115914;
        constexpr unsigned int KO_SND_FNC = 0x00704070;
        constexpr unsigned int KO_FMBS = 0x0050DEB0;
        constexpr unsigned int KO_FLDB = 0x01115840;
        
        constexpr unsigned int KO_PTR_LOGIN_REQUEST2 = 0x007BDD00;
        constexpr unsigned int KO_PTR_LOAD_SERVER_LIST = 0x00BD25D0;
        constexpr unsigned int KO_PTR_SERVER_SELECT = 0x00BD2440;
        constexpr unsigned int KO_PTR_SHOW_CHANNEL = 0x00BD2990;
        constexpr unsigned int KO_PTR_SELECT_CHANNEL = 0x00BD2370;
        constexpr unsigned int KO_PTR_CONNECT_SERVER = 0x007B2670;

        // Inventory
        constexpr unsigned int KO_OFF_INV = 0x1D8;
        constexpr unsigned int KO_OFF_INV_START = 0x298;
        constexpr unsigned int KO_OFF_DURABILITY = 0x6C;
        constexpr unsigned int KO_OFF_INV_COUNT = 0x68;

        // Player Offsets
        constexpr unsigned int KO_OFF_ID = 0x6A0;
        constexpr unsigned int KO_OFF_NAME = 0x6A4;
        constexpr unsigned int KO_OFF_HP = 0x6D8;
        constexpr unsigned int KO_OFF_MAX_HP = 0x6D4;
        constexpr unsigned int KO_OFF_MP = 0xBF0;
        constexpr unsigned int KO_OFF_MAX_MP = 0xBEC;
        constexpr unsigned int KO_OFF_CLASS = 0x6CC;
        constexpr unsigned int KO_OFF_LVL = 0x6D0;
        constexpr unsigned int KO_OFF_GOLD = 0xBFC;
        
        // Positioning
        constexpr unsigned int KO_OFF_X = 0x3CC;
        constexpr unsigned int KO_OFF_Y = 0x3D4;
        constexpr unsigned int KO_OFF_Z = 0x194;
        constexpr unsigned int KO_OFF_WH = 0x6DC;
        constexpr unsigned int KO_OFF_ZONE = 0xC90;
        constexpr unsigned int KO_OFF_NATION = 0x6C4;
        
        // Progression
        constexpr unsigned int KO_OFF_EXP = 0xC60;
        constexpr unsigned int KO_OFF_MAX_EXP = 0xC58;
        constexpr unsigned int KO_OFF_WEIGHT = 0xC78;
        constexpr unsigned int KO_OFF_MAX_WEIGHT = 0xC70;

        // Combat
        constexpr unsigned int KO_OFF_ATTACK = 0xCAC;
        constexpr unsigned int KO_OFF_DEFENCE = 0xCB4;
        constexpr unsigned int KO_OFF_TARGET_MOVE = 0x3AC;
        constexpr unsigned int KO_OFF_TARGET_STATU = 0x270;
        constexpr unsigned int KO_OFF_MOB = 0x6D4;
        constexpr unsigned int KO_OFF_LOOT = 0x948;
        constexpr unsigned int KO_OFF_SKILL_BASE = 0x21C;
    }
}
