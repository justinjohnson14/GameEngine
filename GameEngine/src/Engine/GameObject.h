#pragma once

#include "Mesh.h"
#include "scripting/ScriptEngine.h"

class GameObject
{
public:
	void BindShader();
	void Render();
private:
	Mesh* m_Mesh;
	Texture* m_Texture;
	Shader* m_Shader;
	Script* m_Script;
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
};

