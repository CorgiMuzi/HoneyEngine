#pragma once
#include "core/ManagerBase.h"
#include "resource/IResourceLoader.h"
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include <functional>
#include <iostream>
#include <filesystem>

namespace HoneyEngine
{
	class Resource;

	class ResourceManager final : public ManagerBase {
	public:
		ResourceManager() = default;

		/**
		 * Loads configurations (e.g., resource types) for the resource manager
		 * @param configPath A path of the configuration json file
		 */
		void loadConfiguration(const std::string& configPath);

		using ResourceLoader = std::function<std::shared_ptr<Resource>(const std::string&)>;

		/**
		 * @brief Registers a resource type with its associated file extensions and creation function
		 * @tparam T The resource class (e.g., Texture, Sound) which must derive from Resource
		 * @param extension A file extensions (e.g., ".png", ".jpg") to associate with this resource type
		 */
		template<typename T>
		void registerExtension(const std::string& extension) {
			registerLoader(extension, [](const std::string& filePath) {
				return std::make_shared<T>(filePath);
			});
		}

		/**
		 *
		 * @param extension
		 * @param loader
		 */
		void registerLoader(const std::string& extension, std::shared_ptr<IResourceLoader> loader);

		/**
		 * @brief Loads a resource of a specific type from a file path
		 * @tparam T The type of the resource to load
		 * @param filePath The path of the resource file
		 * @return A shared_ptr to the loaded resource, or nullptr if loading fails
		 */
		template<typename T>
		std::shared_ptr<T> load(const std::string& filePath) {
			std::shared_ptr<Resource> resource = loadResource(filePath);
			if (!resource) return nullptr; // Loading fails

			std::shared_ptr<T> castedResource = std::dynamic_pointer_cast<T>(resource);
			if (!castedResource) {
				std::cerr << "Error: Resource type mismatch for file: " << filePath << std::endl;
			}
			return castedResource;
		}

		/**
		 * @brief Unloads the resource from the memory
		 * @param filePath The path of the resource that unloaded from the memory
		 */
		void unloadResource(const std::string& filePath);

		/**
		 * Unloads all resources from the memory
		 */
		void unloadAllResources();

	private:
		std::shared_ptr<Resource> loadResource(const std::string& filePath);

		// Maps file extension (e.g., ".png") to a name of the resource class
		std::unordered_map<std::string, std::string> m_extensionToTypeMap;
		// Maps resource type (e.g., "Surface", "Sound") to a function that creates a resource of the correct type
		std::unordered_map<std::string, std::shared_ptr<IResourceLoader>> m_loaders;
		// Caches loaded resources to avoid redundant loading
		std::unordered_map<std::string, std::shared_ptr<Resource>> m_resourceCache;
	};
}