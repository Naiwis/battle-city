#pragma once
#include <string>
#include <memory>
#include <map>

namespace Renderer
{
	class ShaderProgram;
	class Texture2D;
}

class ResourceManager
{
public:
	ResourceManager(const std::string executablePath);
	~ResourceManager() = default;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	std::shared_ptr <Renderer::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	std::shared_ptr <Renderer::ShaderProgram> getShaderProgram(const std::string& shaderName);
	std::shared_ptr <Renderer::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
	std::shared_ptr <Renderer::Texture2D> getTexture(const std::string& textureName);

private:
	std::string getFileString(const std::string& relativeFilePath) const;
	using ShaderProgramMap = std::map< const std::string, std::shared_ptr <Renderer::ShaderProgram>>;
	ShaderProgramMap m_shaderProgram;

	using TexturesMap = std::map< const std::string, std::shared_ptr <Renderer::Texture2D>>;
	TexturesMap m_textures;

	std::string m_path;
};