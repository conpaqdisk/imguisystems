#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include <Windows.h>

namespace KOPacket {

    constexpr uint8_t WIZ_ITEM_DROP       = 0x23;
    constexpr uint8_t WIZ_BUNDLE_OPEN_REQ = 0x24;
    constexpr uint8_t WIZ_ITEM_GET        = 0x26;

    struct BundleInfo {
        uint32_t bundleId;
        uint64_t noah;
        std::vector<uint32_t> itemIds;
        std::vector<uint16_t> itemCounts;
    };

    using SendFunc = void(*)(const uint8_t*, size_t);
    using RecvFunc = bool(*)(uint8_t*, size_t*);

    class BundleManager {
    public:
        BundleManager(SendFunc sendFn, RecvFunc recvFn, HANDLE hProcess, uintptr_t baseAddr);
        ~BundleManager();

        bool OpenBundle(uint32_t bundleId, BundleInfo& outInfo);
        bool GetNoah(uint32_t bundleId, uint64_t amount);
        bool GetItem(uint32_t bundleId, uint32_t itemId, uint16_t count);

    private:
        std::vector<uint8_t> BuildBundleOpenReq(uint32_t bundleId);
        std::vector<uint8_t> BuildItemGetNoah(uint32_t bundleId, uint64_t amount);
        std::vector<uint8_t> BuildItemGetItem(uint32_t bundleId, uint32_t itemId, uint16_t count);

        bool ParseBundleOpenResp(const uint8_t* data, size_t len, BundleInfo& outInfo);
        bool ParseItemGetResp(const uint8_t* data, size_t len);

        template<typename T>
        bool ReadMemory(uintptr_t address, T& value) const;
        template<typename T>
        bool WriteMemory(uintptr_t address, const T& value) const;

        SendFunc m_sendFn;
        RecvFunc m_recvFn;
        HANDLE   m_hProcess;
        uintptr_t m_baseAddr;

        static constexpr int RECV_TIMEOUT_MS = 2000;
    };

}
