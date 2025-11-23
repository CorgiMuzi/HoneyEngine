#pragma once
#include <string>
#include "resource/ResourceManager.h"

namespace HoneyEngine {
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
