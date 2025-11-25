#pragma once
#include "utils/StringRegistry.h"
#include "resource/ResourceManager.h"

namespace HoneyEngine {
    struct ResourceID {
        uint32_t value;

        ResourceID() = default;
        explicit ResourceID(const std::string& source) {
            value = StringRegistry::getInstance()->addString(source);
        }
        explicit ResourceID(const uint32_t id) : value(id) {}

        std::string getResourceName() const { return StringRegistry::getInstance()->getString(value); }

        bool operator==(const ResourceID& other) const { return value == other.value; }
        bool operator!=(const ResourceID& other) const { return value != other.value; }
        bool operator<(const ResourceID& other) const { return value < other.value; }
    };

    class Resource {
    public:
        explicit Resource(const std::string& filePath) : m_filePath(filePath) {}
        virtual ~Resource() = default;

        Resource(const Resource&) = delete;
        Resource& operator=(const Resource&) = delete;

    private:
        friend ResourceManager;
        std::string m_filePath;

    public:
        const std::string& getFilePath() const { return m_filePath; }
    };
}

template<> struct std::hash<HoneyEngine::ResourceID> {
    std::size_t operator()(const HoneyEngine::ResourceID& id) const noexcept {
        return id.value;
    }
};
