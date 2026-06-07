#pragma once
#include "utils/StringRegistry.h"
#include <format>
#include <string>

namespace HoneyEngine {
    /**
     * @brief A lightweight identifier that combines a hash-based ID with debug name lookup.
     * Used throughout the engine for efficient identification with human-readable debugging.
     */
    struct NamedID {
        uint32_t value{0};

        NamedID() = default;

        explicit NamedID(const std::string& name) {
            value = StringRegistry::getInstance()->addString(name);
        }

        explicit NamedID(uint32_t id) : value(id) {}

        /**
         * @brief Get the debug name with ID in format "Name[12345]"
         */
        std::string getDebugName() const {
            return std::format("{}[{}]", StringRegistry::getInstance()->getString(value), value);
        }

        /**
         * @brief Get just the name without the hash ID
         */
        std::string getName() const {
            return StringRegistry::getInstance()->getString(value);
        }

        bool operator==(const NamedID& other) const { return value == other.value; }
        bool operator!=(const NamedID& other) const { return value != other.value; }
        bool operator<(const NamedID& other) const { return value < other.value; }
    };
}

// Hash function for use in std::unordered_map
template<> struct std::hash<HoneyEngine::NamedID> {
    std::size_t operator()(const HoneyEngine::NamedID& id) const noexcept {
        return id.value;
    }
};
