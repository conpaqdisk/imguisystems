#pragma once
#include <cstdint>

namespace Core
{
    namespace Packets
    {
        // Kutu (Loot) Sistemi Paket ID'leri ve Isleyis Yapisi
        
        // 1. Mob olup kutu dusunce gelen RECV paketi
        // Ornek: 23 31B20000 6F740000 01
        constexpr uint8_t WIZ_ITEM_DROP = 0x23; 
        
        // 2. Kutunun icerigini gormek icin gonderilen SEND paketi ve
        // 3. Kutunun icerigindeki noah/item bilgilerini tasiyan RECV paketi
        // Send Ornek: 24 6F740000
        // Recv Ornek: 24 6F740000 0100 E9A43503 00 50FF4D30 0100 ...
        constexpr uint8_t WIZ_BUNDLE_OPEN_REQ = 0x24;
        
        // 4. Kutunun icerigindeki noah ve itemleri almak icin gonderilen SEND paketi ve
        // 5. Kutunun icerigindeki itemleri aldigimizi onaylayan RECV paketi
        // Send Ornek (Noah): 26 6F740000 00 E9A43500 00
        // Send Ornek (Item): 26 6F740000 50 FF4D3001 00
        // Recv Ornek: 26 01 6F740000 FF 00 E9A43503 00 0FC22602
        constexpr uint8_t WIZ_ITEM_GET = 0x26;

        #pragma pack(push, 1)

        struct PktItemDropRecv {
            uint8_t header; // 0x23
            uint32_t mobId;
            uint32_t bundleId;
        };

        struct PktBundleOpenReqSend {
            uint8_t header; // 0x24
            uint32_t bundleId;
        };

        struct PktItemGetSend {
            uint8_t header; // 0x26
            uint32_t bundleId;
            uint32_t itemId; // 0 for Noah
            // ... offset details
        };

        #pragma pack(pop)
    }
}
