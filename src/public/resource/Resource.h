#pragma once
#include "utils/INamedObject.h"
#include "utils/NamedID.h"
#include "resource/ResourceManager.h"

namespace HoneyEngine {
    // Type alias for backwards compatibility
    using ResourceID = NamedID;

    class Resource : public INamedObject {
    public:
        explicit Resource(const std::string& filePath)
            : INamedObject(filePath), m_filePath(filePath) {}
        virtual ~Resource() = default;

        Resource(const Resource&) = delete;
        Resource& operator=(const Resource&) = delete;

    private:
        friend ResourceManager;
        std::string m_filePath;

    public:
        const std::string& getFilePath() const { return m_filePath; }

        // Get ResourceID (which is now NamedID)
        const ResourceID& getResourceID() const { return m_namedID; }
    };
}
