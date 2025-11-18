#pragma once
#include "core/ManagerBase.h"
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
		 * @brief Registers a resource type with its associated file extensions and creation function
		 * @tparam T The resource class (e.g., Texture, Sound) which must derive from Resource
		 * @param extensions A list of file extensions (e.g., {".png", ".jpg"}) to associate with this resource type
		 */
		template<typename T>
		void registerResourceType(const std::vector<std::string>& extensions) {
			static_assert(std::is_base_of_v<Resource, T>, "T must be a subclass of Resource");
			for (const auto& ext : extensions) {
				if (m_resourceFactory.contains(ext)) {
					std::cerr << "Warning: Overwriting registration for extension - " << ext << std::endl;
				}
				m_resourceFactory[ext] = [](const std::string& filePath) {
					return std::make_shared<T>(filePath);
				};
			}
		}

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

		// Waiting list of resources to load
		std::vector<std::string> m_resourceQueue;
		// Maps file extension (e.g., ".png") to a function that creates a resource of the correct type
		std::unordered_map<std::string, std::function<std::shared_ptr<Resource>(const std::string&)>> m_resourceFactory;
		// Caches loaded resources to avoid redundant loading
		std::unordered_map<std::string, std::shared_ptr<Resource>> m_resourceCache;
	};
}