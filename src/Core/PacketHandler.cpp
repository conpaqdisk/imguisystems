#include "PacketHandler.h"
#include <cstring>
#include <chrono>
#include <thread>
#include <stdexcept>

namespace KOPacket {

    BundleManager::BundleManager(SendFunc sendFn, RecvFunc recvFn, HANDLE hProcess, uintptr_t baseAddr)
        : m_sendFn(sendFn), m_recvFn(recvFn), m_hProcess(hProcess), m_baseAddr(baseAddr) {
        if (!m_sendFn || !m_recvFn || !m_hProcess) {
            throw std::runtime_error("Invalid function pointers or process handle");
        }
    }

    BundleManager::~BundleManager() {
    }

    bool BundleManager::OpenBundle(uint32_t bundleId, BundleInfo& outInfo) {
        auto req = BuildBundleOpenReq(bundleId);
        m_sendFn(req.data(), req.size());

        uint8_t buffer[512];
        size_t len = sizeof(buffer);
        if (!m_recvFn(buffer, &len) || len < 8) {
            return false;
        }

        return ParseBundleOpenResp(buffer, len, outInfo);
    }

    bool BundleManager::GetNoah(uint32_t bundleId, uint64_t amount) {
        auto req = BuildItemGetNoah(bundleId, amount);
        m_sendFn(req.data(), req.size());

        uint8_t buffer[128];
        size_t len = sizeof(buffer);
        if (!m_recvFn(buffer, &len)) {
            return false;
        }
        return ParseItemGetResp(buffer, len);
    }

    bool BundleManager::GetItem(uint32_t bundleId, uint32_t itemId, uint16_t count) {
        auto req = BuildItemGetItem(bundleId, itemId, count);
        m_sendFn(req.data(), req.size());

        uint8_t buffer[128];
        size_t len = sizeof(buffer);
        if (!m_recvFn(buffer, &len)) {
            return false;
        }
        return ParseItemGetResp(buffer, len);
    }

    std::vector<uint8_t> BundleManager::BuildBundleOpenReq(uint32_t bundleId) {
        std::vector<uint8_t> pkt;
        pkt.reserve(5);
        pkt.push_back(WIZ_BUNDLE_OPEN_REQ);
        pkt.push_back(static_cast<uint8_t>(bundleId & 0xFF));
        pkt.push_back(static_cast<uint8_t>((bundleId >> 8) & 0xFF));
        pkt.push_back(static_cast<uint8_t>((bundleId >> 16) & 0xFF));
        pkt.push_back(static_cast<uint8_t>((bundleId >> 24) & 0xFF));
        return pkt;
    }

    std::vector<uint8_t> BundleManager::BuildItemGetNoah(uint32_t bundleId, uint64_t amount) {
        std::vector<uint8_t> pkt;
        pkt.reserve(13);
        pkt.push_back(WIZ_ITEM_GET);
        for (int i = 0; i < 4; ++i) pkt.push_back((bundleId >> (8*i)) & 0xFF);
        pkt.push_back(0x00);
        for (int i = 0; i < 8; ++i) pkt.push_back((amount >> (8*i)) & 0xFF);
        return pkt;
    }

    std::vector<uint8_t> BundleManager::BuildItemGetItem(uint32_t bundleId, uint32_t itemId, uint16_t count) {
        std::vector<uint8_t> pkt;
        pkt.reserve(12);
        pkt.push_back(WIZ_ITEM_GET);
        for (int i = 0; i < 4; ++i) pkt.push_back((bundleId >> (8*i)) & 0xFF);
        for (int i = 0; i < 4; ++i) pkt.push_back((itemId >> (8*i)) & 0xFF);
        pkt.push_back(count & 0xFF);
        pkt.push_back((count >> 8) & 0xFF);
        return pkt;
    }

    bool BundleManager::ParseBundleOpenResp(const uint8_t* data, size_t len, BundleInfo& outInfo) {
        if (len < 8 || data[0] != WIZ_BUNDLE_OPEN_REQ) return false;

        uint32_t id = 0;
        for (int i = 0; i < 4; ++i) id |= (data[1+i] << (8*i));
        if (id != outInfo.bundleId) return false;

        if (data[5] != 0x01) return false;

        size_t offset = 6;
        bool hasNoah = false;
        if (offset < len && data[offset] == 0x00) {
            offset++;
            if (offset + 4 <= len) {
                outInfo.noah = 0;
                for (int i = 0; i < 4; ++i) outInfo.noah |= (static_cast<uint64_t>(data[offset+i]) << (8*i));
                offset += 4;
                hasNoah = true;
            }
        }

        while (offset + 5 <= len) {
            if (data[offset] == 0x01) {
                offset++;
                uint32_t itemId = 0;
                for (int i = 0; i < 4; ++i) itemId |= (data[offset+i] << (8*i));
                offset += 4;
                uint16_t count = 0;
                count |= data[offset];
                count |= (data[offset+1] << 8);
                offset += 2;
                outInfo.itemIds.push_back(itemId);
                outInfo.itemCounts.push_back(count);
            } else {
                break;
            }
        }
        return true;
    }

    bool BundleManager::ParseItemGetResp(const uint8_t* data, size_t len) {
        if (len < 6 || data[0] != WIZ_ITEM_GET) return false;
        return (data[1] == 0x01);
    }

    template<typename T>
    bool BundleManager::ReadMemory(uintptr_t address, T& value) const {
        SIZE_T bytesRead;
        return ReadProcessMemory(m_hProcess, reinterpret_cast<LPCVOID>(address), &value, sizeof(T), &bytesRead) && bytesRead == sizeof(T);
    }

    template<typename T>
    bool BundleManager::WriteMemory(uintptr_t address, const T& value) const {
        SIZE_T bytesWritten;
        return WriteProcessMemory(m_hProcess, reinterpret_cast<LPVOID>(address), &value, sizeof(T), &bytesWritten) && bytesWritten == sizeof(T);
    }

}
