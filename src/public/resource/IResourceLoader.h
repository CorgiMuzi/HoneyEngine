#pragma once
#include <memory>
#include <string>

namespace HoneyEngine {
    class Resource;

    class IResourceLoader {
    public:
        virtual ~IResourceLoader() = default;
        virtual std::shared_ptr<Resource> load(const std::string& filePath) = 0;
    };
}