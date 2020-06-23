#include "Mesh.h"

#include <algorithm>

Texture* texture;
std::array<Vertex, 24> CreateQuad(const glm::vec3& size);

Mesh::Mesh(const glm::vec3& demensions, const glm::vec3& position, const glm::vec3& rotation, Shader*& shader)
	: m_Position(position), m_Rotation(rotation), m_Scale(demensions), m_Shader(shader)
{
	m_Model = glm::scale(m_Model, glm::vec3(1,1,1));
	m_Model = glm::translate(m_Model, m_Position);
	m_Model = glm::rotate(m_Model, glm::radians(90.0f), glm::vec3(1, 0, 0));
	m_Model = glm::rotate(m_Model, m_Rotation.y, glm::vec3(0, 1, 0));
	m_Model = glm::rotate(m_Model, m_Rotation.z, glm::vec3(0, 0, 1));

	unsigned int m_Indices[] = {
		0,1,2,2,3,0,
		4,5,6,6,7,4,
		8,9,10,10,11,8,
		12,13,14,14,15,12,
		16,17,18,18,19,16,
		20,21,22,22,23,20,
	};

	//texture = new Texture("src/resources/textures/Simple blocks textures/assets/minecraft/textures/block/diamond_block.png");
	m_Texture = new Texture("src/resources/textures/wall.jpg");

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	m_Shader->Bind();

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 1000, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Vertices));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex,TextureCoords));
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TextureID));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Indices), m_Indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	m_Shader->Unbind();
}

Mesh::Mesh(std::vector<Vertex> m_Vertices, std::vector<unsigned int> Indices, Texture* texture)
{
	m_Shader = new Shader("src/resources/shaders/Test.glsl");

	m_Model = glm::scale(m_Model, glm::vec3(1, 1, 1));
	m_Model = glm::translate(m_Model, m_Position);
	m_Model = glm::rotate(m_Model, glm::radians(90.0f), glm::vec3(1, 0, 0));
	m_Model = glm::rotate(m_Model, m_Rotation.y, glm::vec3(0, 1, 0));
	m_Model = glm::rotate(m_Model, m_Rotation.z, glm::vec3(0, 0, 1));

	m_Texture = texture;
	vertices = m_Vertices;
	indices = Indices;

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	m_Shader->Bind();

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Vertices));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TextureCoords));
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TextureID));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), (const void*)&indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	m_Shader->Unbind();
}

void Mesh::Update()
{
	m_Model = glm::translate(m_Model, glm::vec3(1) * m_Velocity);
	//m_Model = glm::rotate(m_Model, 0.005f, glm::vec3(1, 0, 0));
}

void Mesh::SetRotation(const glm::vec3& rot)
{
	m_Model = glm::rotate(m_Model, glm::radians(90.0f), glm::vec3(1, 0, 0));
	m_Model = glm::rotate(m_Model, m_Rotation.y, glm::vec3(0, 1, 0));
	m_Model = glm::rotate(m_Model, m_Rotation.z, glm::vec3(0, 0, 1));
}

std::array<Vertex, 24> CreateQuad(const glm::vec3& size)
{
	Vertex v0;
	v0.Vertices = glm::vec3(0.0, 0.0, 0.5);
	v0.TextureCoords = glm::vec2(0.0, 0.0);
	v0.TextureID = 0.0;
	Vertex v1;
	v1.Vertices = glm::vec3(size.x, 0.0, 0.5);
	v1.TextureCoords = glm::vec2(1.0, 0.0);
	v1.TextureID = 0.0;
	Vertex v2;
	v2.Vertices = glm::vec3(size.x, size.y, 0.5);
	v2.TextureCoords = glm::vec2(1.0, 1.0);
	v2.TextureID = 0.0;
	Vertex v3;
	v3.Vertices = glm::vec3(0.0, size.y, 0.5);
	v3.TextureCoords = glm::vec2(0.0, 1.0);
	v3.TextureID = 0.0;

	Vertex v4;
	v4.Vertices = glm::vec3(size.x, 0.0, 0.5);
	v4.TextureCoords = glm::vec2(0.0, 0.0);
	v4.TextureID = 0.0;
	Vertex v5;
	v5.Vertices = glm::vec3(size.x, 0.0, size.z - size.z * 1.5);
	v5.TextureCoords = glm::vec2(1.0, 0.0);
	v5.TextureID = 0.0;
	Vertex v6;
	v6.Vertices = glm::vec3(size.x, size.y, size.z - size.z * 1.5);
	v6.TextureCoords = glm::vec2(1.0, 1.0);
	v6.TextureID = 0.0;
	Vertex v7;
	v7.Vertices = glm::vec3(size.x, size.y, 0.5);
	v7.TextureCoords = glm::vec2(0.0, 1.0);
	v7.TextureID = 0.0;

	Vertex v8;
	v8.Vertices = glm::vec3(size.x, 0.0, size.z - size.z * 1.5);
	v8.TextureCoords = glm::vec2(0.0, 0.0);
	v8.TextureID = 0.0;
	Vertex v9;
	v9.Vertices = glm::vec3(0.0, 0.0, size.z - size.z * 1.5);
	v9.TextureCoords = glm::vec2(1.0, 0.0);
	v9.TextureID = 0.0;
	Vertex v10;
	v10.Vertices = glm::vec3(0.0, size.y, size.z - size.z * 1.5);
	v10.TextureCoords = glm::vec2(1.0, 1.0);
	v10.TextureID = 0.0;
	Vertex v11;
	v11.Vertices = glm::vec3(size.x, size.y, size.z - size.z * 1.5);
	v11.TextureCoords = glm::vec2(0.0, 1.0);
	v11.TextureID = 0.0;

	Vertex v12;
	v12.Vertices = glm::vec3(0.0, 0.0, size.z - size.z * 1.5);
	v12.TextureCoords = glm::vec2(0.0, 0.0);
	v12.TextureID = 0.0;
	Vertex v13;
	v13.Vertices = glm::vec3(0.0, 0.0, 0.5);
	v13.TextureCoords = glm::vec2(1.0, 0.0);
	v13.TextureID = 0.0;
	Vertex v14;
	v14.Vertices = glm::vec3(0.0, size.y, 0.5);
	v14.TextureCoords = glm::vec2(1.0, 1.0);
	v14.TextureID = 0.0;
	Vertex v15;
	v15.Vertices = glm::vec3(0.0, size.y, size.z - size.z * 1.5);
	v15.TextureCoords = glm::vec2(0.0, 1.0);
	v15.TextureID = 0.0;

	Vertex v16;
	v16.Vertices = glm::vec3(0.0, size.y, 0.5);
	v16.TextureCoords = glm::vec2(0.0, 0.0);
	v16.TextureID = 0.0;
	Vertex v17;
	v17.Vertices = glm::vec3(size.x, size.y, 0.5);
	v17.TextureCoords = glm::vec2(1.0, 0.0);
	v17.TextureID = 0.0;
	Vertex v18;
	v18.Vertices = glm::vec3(size.x, size.y, size.z - size.z * 1.5);
	v18.TextureCoords = glm::vec2(1.0, 1.0);
	v18.TextureID = 0.0;
	Vertex v19;
	v19.Vertices = glm::vec3(0.0, size.y, size.z - size.z * 1.5);
	v19.TextureCoords = glm::vec2(0.0, 1.0);
	v19.TextureID = 0.0;

	Vertex v20;
	v20.Vertices = glm::vec3(0.0, 0.0, size.z - size.z * 1.5);
	v20.TextureCoords = glm::vec2(0.0, 0.0);
	v20.TextureID = 0.0;
	Vertex v21;
	v21.Vertices = glm::vec3(size.x, 0.0, size.z - size.z * 1.5);
	v21.TextureCoords = glm::vec2(1.0, 0.0);
	v21.TextureID = 0.0;
	Vertex v22;
	v22.Vertices = glm::vec3(size.x, 0.0, 0.5);
	v22.TextureCoords = glm::vec2(1.0, 1.0);
	v22.TextureID = 0.0;
	Vertex v23;
	v23.Vertices = glm::vec3(0.0, 0.0, 0.5);
	v23.TextureCoords = glm::vec2(0.0, 1.0);
	v23.TextureID = 0.0;

	return { v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23};
}

void Mesh::Render(Camera*& camera)
{
	
	//auto quad = CreateQuad(m_Scale);
	//Vertex vertices[24];
	//memcpy(vertices, quad.data(), quad.size() * sizeof(Vertex));
	

	m_Shader->Bind();
	m_Shader->SetMat4("u_Model", m_Model);
	m_Shader->SetMat4("u_View", camera->GetViewMatrix());
	m_Texture->Bind();
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), (const void*)&vertices[0]);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
	m_Shader->Unbind();
}

void Mesh::SetVelocity(const glm::vec3& vel)
{
	m_Velocity = vel;
}