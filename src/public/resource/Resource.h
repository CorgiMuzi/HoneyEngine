#pragma once
#include <string>

namespace HoneyEngine
{
	class ResourceManager;

	class Resource {
	public:
		virtual ~Resource() = default;

		Resource(const Resource&) = delete;
		Resource& operator=(const Resource&) = delete;

		virtual bool load() = 0;

		explicit Resource(const std::string& filePath) : m_filePath(filePath) {}
	protected:


	private:
		friend ResourceManager;
		std::string m_filePath;

	public:
		const std::string& getFilePath() const { return m_filePath; }
	};
}