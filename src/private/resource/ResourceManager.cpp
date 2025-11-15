#include <SDL3_image/SDL_image.h>
#include "resource/ResourceManager.h"
#include "resource/Resource.h"

namespace HoneyEngine
{
	ResourceManager::ResourceManager() {
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

		SDL_Surface* surface = IMG_Load(filePath.c_str());
		if (!surface) return false;

		const auto resource = std::shared_ptr<Resource>(new Resource(surface));
		m_resourceCache[filePath] = resource;

		return true;
	}
}