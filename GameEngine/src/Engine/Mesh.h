#pragma once

#include <Shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Camera.h>
#include "Texture.h"

#include <array>

struct Vertex
{
	glm::vec3 Vertices;
	glm::vec2 TextureCoords;
	glm::vec3 NormalCoords;
	glm::vec3 SpecCoords;
	float TextureID;
};

class Mesh
{
public:
	Mesh(const glm::vec3&,const glm::vec3&, const glm::vec3&,Shader*&);
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Texture* texture);

	void Render(Camera*&);
	void Update();
	void SetVelocity(const glm::vec3&);
	void SetRotation(const glm::vec3&);
	Shader* GetShader() { return m_Shader; }
private:
	GLuint m_VAO, m_VBO, m_IBO;
	int m_Width, m_Height;
	glm::vec3 m_Position = glm::vec3(1.0f);
	glm::vec3 m_Rotation = glm::vec3(1.0f);
	glm::vec3 m_Scale = glm::vec3(1.0f);
	glm::vec3 m_Velocity = glm::vec3(0.0f);
	glm::mat4 m_View = glm::mat4(1.0f);
	glm::mat4 m_Model = glm::mat4(1.0f);
	std::vector<Vertex> vertices;
	Texture* m_Texture;
	std::vector<unsigned int> indices;
	Shader* m_Shader;
};

