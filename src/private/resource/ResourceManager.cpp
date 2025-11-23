#include "resource/ResourceManager.h"
#include "resource/Resource.h"
#include "resource/IResourceLoader.h"
#include <fstream>
#include <SDL3/SDL_log.h>
#include <nlohmann/json.hpp>

namespace HoneyEngine
{
	using JsonFile=nlohmann::json;

	void ResourceManager::registerLoader(const std::string& typeName, std::shared_ptr<IResourceLoader> loader) {
		m_loaders[typeName] = std::move(loader);
	}

	void ResourceManager::loadConfiguration(const std::string& configPath) {
		std::fstream configFile(configPath);
		if (!configFile.is_open()) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to open configuration file from : %s", configPath.c_str());
			return;
		}

		JsonFile configJson;
		try {
			configFile >> configJson;
		}catch(std::exception& e) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to parse configuration file at '%s'.\nError: %s", configPath.c_str(), e.what());
		}

		SDL_Log("Successfully loaded configuration file at '%s'.", configPath.c_str());

		if (!configJson.contains("resource_types") || !configJson["resource_types"].is_array()) {
			SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Config file is missing 'resource-types' array.");
			return;
		}

		for (const auto& entry : configJson["resource_types"]) {
			if (!entry.contains("type_name") || !entry["type_name"].is_string()) {
				SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Skipping type entry with invalid 'type_name' in resource config.");
				continue;
			}

			if (!entry.contains("extensions") || !entry["extensions"].is_array()) {
				SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Skipping type entry for '%s' with invalid 'extensions'.", entry["type_name"].get<std::string>().c_str());
				continue;
			}

			const std::string typeName = entry["type_name"].get<std::string>();
			for (const auto& extension : entry["extensions"]) {
				m_extensionToTypeMap[extension.get<std::string>()] = typeName;
			}
		}
	}

	std::shared_ptr<Resource> ResourceManager::loadResource(const std::string& filePath) {
		if (m_resourceCache.contains(filePath)) return m_resourceCache[filePath];

		std::string fileExtension = std::filesystem::path(filePath).extension().string();
		if (!m_extensionToTypeMap.contains(fileExtension)) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unknown file extension : %s", fileExtension.c_str());
			return nullptr;
		}

		std::string typeName = m_extensionToTypeMap[fileExtension];
		if (!m_loaders.contains(typeName)) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to find an appropriate loader for this resource type : %s", typeName.c_str());
			return nullptr;
		}

		std::shared_ptr<Resource> newResource = m_loaders[typeName]->load(filePath);

		if (!newResource) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load a resource from %s", filePath.c_str());
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
