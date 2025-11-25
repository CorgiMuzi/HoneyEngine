#include "utils/StringRegistry.h"
#include <algorithm>

namespace HoneyEngine {
    uint32_t StringRegistry::addString(std::string_view str) {
        uint32_t hash = hashString(str);

        if (!m_registry.contains(hash)) {
            m_registry[hash] = std::string(str);
        }

        return hash;
    }

    std::string StringRegistry::getString(uint32_t hash) const {
        auto iter = m_registry.find(hash);

        if (iter != m_registry.end()) return iter->second;
        return std::string("Unknown");
    }
}
