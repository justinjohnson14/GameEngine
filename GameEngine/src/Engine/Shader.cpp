#include "Shader.h"

#include <fstream>
#include <array>

#include <glm/gtc/type_ptr.hpp>

#include "Log.h"
#include "Core.h"

static GLenum ShaderTypeFromString(const std::string& type)
{
	if (type == "vertex")
		return GL_VERTEX_SHADER;
	if (type == "fragment" || type == "pixel")
		return GL_FRAGMENT_SHADER;

	return 0;
}

Shader::Shader(const std::string& filepath)
{
	std::string source = ReadFile(filepath);
	auto shaderSources = PreProcess(source);

	Compile(shaderSources);
}

Shader::Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
{
	std::unordered_map<GLenum, std::string> sources;
	sources[GL_VERTEX_SHADER] = vertexSrc;
	sources[GL_FRAGMENT_SHADER] = fragmentSrc;
	Compile(sources);
}

Shader::~Shader()
{
	glDeleteProgram(m_ID);
}

std::string Shader::ReadFile(const std::string& filepath)
{
	std::string result;
	std::ifstream in(filepath, std::ios::in | std::ios::binary);
	if (in)
	{
		in.seekg(0, std::ios::end);
		size_t size = in.tellg();
		if (size != -1)
		{
			result.resize(size);
			in.seekg(0, std::ios::beg);
			in.read(&result[0], size);
			in.close();
		}
	}
	else
	{
		ENGINE_LOG_WARN("Could not read file{0}", filepath);
	}

	return result;
}

std::unordered_map<GLenum, std::string> Shader::PreProcess(const std::string& source)
{
	std::unordered_map<GLenum, std::string> shaderSources;

	const char* typeToken = "#type";
	size_t typeTokenLength = strlen(typeToken);
	size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
	while (pos != std::string::npos)
	{
		size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
		ENGINE_ASSERT_MESSAGE(eol != std::string::npos, "Syntax error");
		size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
		std::string type = source.substr(begin, eol - begin);
		ENGINE_ASSERT_MESSAGE(type == "vertex" || type == "fragment" || type == "pixel", "Invalid shader type specified");


		size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
		pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line

		shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);

	}

	return shaderSources;
}

void Shader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
{
	GLuint program = glCreateProgram();
	std::array<GLenum, 2> glShaderIDs;
	int glShaderIDIndex = 0;
	for (auto& kv : shaderSources)
	{
		GLenum type = kv.first;
		const std::string& source = kv.second;

		GLuint shader = glCreateShader(type);

		const GLchar* sourceCStr = source.c_str();
		glShaderSource(shader, 1, &sourceCStr, 0);

		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(shader);
			break;
		}

		glAttachShader(program, shader);
		glShaderIDs[glShaderIDIndex++] = shader;
	}

	m_ID = program;

	// Link our program
	glLinkProgram(program);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(program);

		for (auto id : glShaderIDs)
			glDeleteShader(id);
		return;
	}

	for (auto id : glShaderIDs)
	{
		glDetachShader(program, id);
		glDeleteShader(id);
	}
}

void Shader::Bind()
{
	glUseProgram(m_ID);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& data)
{
	UploadUniformMat4(name, data);
}

void Shader::SetFloat(const std::string& name, const float data)
{
	UploadUniformFloat(name, data);
}

void Shader::SetFloat3(const std::string& name, const glm::vec3& data)
{
	UploadUniformFloat3(name, data);
}

void Shader::SetFloat4(const std::string& name, const glm::vec4& data)
{
	UploadUniformFloat4(name, data);
}

void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& data)
{
	GLint loc = glGetUniformLocation(m_ID, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(data));
}

void Shader::UploadUniformFloat(const std::string& name, const float data)
{
	GLint loc = glGetUniformLocation(m_ID, name.c_str());
	glUniform1f(loc, data);
}

void Shader::UploadUniformFloat3(const std::string& name, const glm::vec3& data)
{
	GLint loc = glGetUniformLocation(m_ID, name.c_str());
	glUniform3fv(loc, 1, glm::value_ptr(data));
}

void Shader::UploadUniformFloat4(const std::string& name, const glm::vec4& data)
{
	GLint loc = glGetUniformLocation(m_ID, name.c_str());
	glUniform4fv(loc, 1, glm::value_ptr(data));
}