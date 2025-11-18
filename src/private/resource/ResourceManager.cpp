#include "resource/ResourceManager.h"
#include "resource/Resource.h"

namespace HoneyEngine
{
	std::shared_ptr<Resource> ResourceManager::loadResource(const std::string& filePath) {
		if (m_resourceCache.contains(filePath)) return m_resourceCache[filePath];

		std::string extension = std::filesystem::path(filePath).extension().string();
		if (!m_resourceFactory.contains(extension)) {
			std::cerr << "Error: No resource loader registered for extension: " << extension << std::endl;
			return nullptr;
		}

		std::shared_ptr<Resource> newResource = m_resourceFactory[extension](filePath);
		if (!newResource || !newResource->load()) {
			std::cerr << "Error: Failed to load resource: " << filePath << std::endl;
			return nullptr;
		}

		return m_resourceCache[filePath] = newResource;
	}

	void ResourceManager::unloadResource(const std::string& filePath) {
		if (m_resourceCache.contains(filePath)) {
			m_resourceCache.erase(filePath);
		}
	}

	void ResourceManager::unloadAllResources() {
		m_resourceCache.clear();
	}
}