#pragma once
#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>

namespace HoneyEngine {
    constexpr uint32_t hashString(std::string_view str) {
        uint32_t hash = 2166136261u;
        for (char c : str) {
            hash ^= static_cast<uint8_t>(c);
            hash *= 16777619u;
        }
        return hash;
    }

    class StringRegistry {
    public:
        static StringRegistry* getInstance() {
            static StringRegistry instance;
            return &instance;
        }

        uint32_t addString(std::string_view str);
        std::string getString(uint32_t hash) const;

    private:
        std::unordered_map<uint32_t, std::string> m_registry;
    };
}