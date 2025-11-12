#pragma once

class EngineBase {
public:
    /**
     * @brief Static function returning static instance of manager class
     * @return Unique instance of manager class
     */
    static EngineBase& GetInstance() {
        static EngineBase instance;
        return instance;
    }

    // Delete copy constructor and assignment operator
    EngineBase(const EngineBase&) = delete;
    EngineBase& operator=(const EngineBase&) = delete;

protected:
    EngineBase() = default;
    virtual ~EngineBase() = default;
};