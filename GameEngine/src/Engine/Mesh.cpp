#include "Mesh.h"

Mesh::Mesh(int width, int height, const glm::vec3& pos)
	: m_Position(pos)
{
	int vertices[3 * 4] = {
		0.0f, 0.0f, -0.5f,
		width, 0.0f, -0.5f,
		width, height, -0.5f,
		0.0f, height, -0.5f,
	};

	int indices[] = { 0,1,2,2,3,0 };

	m_Shader = new Shader("src/resources/shaders/basic.glsl");
	m_Shader->Bind();

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indices, GL_STATIC_DRAW);

	m_Transformation = glm::mat4(1.0f);
}

void Mesh::UploadViewProj()
{
	m_ViewProjection = glm::ortho(-(800.0f / 2.0f), (800.0f / 2.0f), -(600.0f / 2.0f), (600.0f / 2.0f), 0.1f, 1000.0f);
	m_Shader->SetMat4("u_ViewProjection", m_ViewProjection);
}

void Mesh::UploadTransformation()
{
	m_Transformation = glm::translate(m_Transformation, m_Position);
	m_Transformation = glm::scale(m_Transformation, glm::vec3(5.0f, 5.0f, 1.0f));

	m_Shader->SetMat4("u_Transformation", m_Transformation);
}