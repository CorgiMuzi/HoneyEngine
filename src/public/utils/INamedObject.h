#pragma once
#include "utils/NamedID.h"
#include <string>

namespace HoneyEngine {
    /**
     * @brief Base class for all engine objects that need debug-friendly naming.
     * Provides consistent naming and identification across GameObjects, Components, Resources, etc.
     */
    class INamedObject {
    public:
        explicit INamedObject(const std::string& name)
            : m_namedID(name) {}

        virtual ~INamedObject() = default;

        /**
         * @brief Get the debug name with hash ID (e.g., "Player[12345]")
         */
        std::string getDebugName() const {
            return m_namedID.getDebugName();
        }

        /**
         * @brief Get just the name without hash ID (e.g., "Player")
         */
        std::string getName() const {
            return m_namedID.getName();
        }

        /**
         * @brief Get the NamedID for this object
         */
        const NamedID& getNamedID() const {
            return m_namedID;
        }

    protected:
        NamedID m_namedID;
    };
}
