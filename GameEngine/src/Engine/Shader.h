#pragma once

#include <glm/glm.hpp>

#include <GL/glew.h>

#include <string>
#include <unordered_map>

typedef unsigned int GLenum;

class Shader
{
public:
	Shader();
	Shader(const std::string&);
	Shader(const std::string&, const std::string&, const std::string&);

	~Shader();

	void Bind();
	void Unbind();
	void SetInt(const std::string&, int);
	void SetFloat3();
	void SetFloat4();
	void SetMat4(const std::string&, const glm::mat4&);

	const std::string& GetName() { return m_Name; }

	void UploadUniformInt(const std::string&, int);
	void UploadUniformFloat(const std::string&, float);
	void UploadUniformFloat2(const std::string&, const glm::vec2&);
	void UploadUniformFloat3(const std::string&, const glm::vec3&);
	void UploadUniformFloat4(const std::string&, const glm::vec4&);

	void UploadUniformMat3(const std::string&, const glm::mat3);
	void UploadUniformMat4(const std::string&, const glm::mat4&);
private:
	std::string ReadFile(const std::string&);
	std::unordered_map<GLenum, std::string> PreProcess(const std::string&);
	void Compile(const std::unordered_map<GLenum, std::string>&);
private:
	uint32_t m_ID;
	std::string m_Name;
};

