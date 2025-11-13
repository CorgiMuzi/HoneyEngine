#pragma once
#include "core/ManagerBase.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

class Resource;

class ResourceManager final : public ManagerBase {
public:
    ResourceManager();

    /**
     * @brief Loads a resource from a file
     * @param filePath The path to the resource file to load
     * @return A shared pointer to the loaded resource
     */
    std::shared_ptr<Resource> loadResource(const std::string& filePath);

    /**
     * @brief Queues resources' file path for batching loading
     * @param filePath The path to the resource file to load
     */
    void queueForLoad(const std::string& filePath);

    /**
     * @brief Loads all resources queued for batching
     */
    void loadAllResources();

    /**
     * @brief Release the specific file from loading queue
     * @param filePath The path to the resource file to release
     */
    void release(const std::string& filePath);

private:
    /**
     * @brief Loads a resource from a file
     * @param filePath The path to the resource file to load
     * @return True if the resource was loaded successfully, false otherwise.
     */
    bool load(const std::string& filePath);

    /**
     * Resource cache : store resources already loaded using the path that exists on the filesystem
     */
    std::unordered_map<std::string, std::shared_ptr<Resource>> m_resourceCache;
    /**
     * Resource queue : store the file path to the resources to be loaded
     */
    std::vector<std::string> m_loadQueue;
};