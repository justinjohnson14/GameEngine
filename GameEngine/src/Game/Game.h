#pragma once

#include "glm/glm.hpp"
#include "Mesh.h"
#include "Camera.h"
#include "Layer.h"
#include "scripting/ScriptEngine.h"

class Game : public Layer
{
public:
	Game();
	void Init();
	void Update(double);
	void Input();
	void Render(double);
	bool MouseButtonEvent(int,int,int);
	void SetProjectionMatrix(float, float);
	void SetColor(const glm::vec4& color);
	glm::mat4 GetProjectionMatrix();
	Camera* camera = new Camera(glm::vec3(0, 0, 3), glm::vec3(0));
	void SetRotation(const glm::vec3&);
private:
	glm::mat4 m_Projection = glm::mat4(1.0f);
	ScriptEngine* se;

	float tps = 20.0f;
	float fps = 60.0f;
	float m_Time;

	Shader* m_Shader;

	uint32_t m_VAO, m_VBO, m_IBO;
};

