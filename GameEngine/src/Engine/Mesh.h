#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class Mesh
{

public:
	Mesh(int, int, const glm::vec3&);

	void UploadViewProj();
	void UploadTransformation();
public:
	uint32_t m_VBO, m_IBO, m_VAO;
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	Shader* m_Shader;
	glm::mat4 m_ViewProjection;
	glm::mat4 m_Transformation;
};
