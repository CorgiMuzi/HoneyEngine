#include <SDL3_image/SDL_image.h>
#include "resource/ResourceManager.h"

ResourceManager::ResourceManager(SDL_Renderer* renderer) : m_renderer(renderer) {
}

std::shared_ptr<Resource> ResourceManager::loadResource(const std::string& filePath) {
    if (m_resourceCache.contains(filePath)) {
        return m_resourceCache[filePath];
    }

    if (load(filePath)) {
        return m_resourceCache[filePath];
    }

    // failed to load file
    return nullptr;
}

void ResourceManager::queueForLoad(const std::string& filePath) {
    if (m_resourceCache.contains(filePath)) return;

    m_loadQueue.emplace_back(filePath);
}

void ResourceManager::loadAllResources() {
    for (const std::string& filePath : m_loadQueue) {
        if (!load(filePath)) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load resource from %s", filePath.c_str());
        }
    }

    m_loadQueue.clear();
}

void ResourceManager::release(const std::string& filePath) {
    m_resourceCache.erase(filePath);
}

bool ResourceManager::load(const std::string& filePath) {
    if (m_resourceCache.contains(filePath)) return true;

    SDL_Texture* raw_tex = IMG_LoadTexture(m_renderer, filePath.c_str());
    if (!raw_tex) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load texture from %s", filePath.c_str());
        return false;
    }

    auto texture = std::shared_ptr<SDL_Texture>(raw_tex, SDLTextureDeleter());

    auto resource = std::make_shared<Resource>(filePath);
    resource->setTexture(texture);

    m_resourceCache[filePath] = resource;
    return true;
}
