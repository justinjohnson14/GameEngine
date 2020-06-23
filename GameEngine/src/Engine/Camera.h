#pragma once

#include <glm/glm.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera
{
public:
	Camera(const glm::vec3&, const glm::vec3&);

	glm::mat4 GetViewMatrix();
	void Move(Camera_Movement);
	void Rotate(const glm::vec3&);
public:
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 m_Position = glm::vec3(0);
	glm::vec3 m_Rotation = glm::vec3(0);
	glm::mat4 m_View = glm::mat4(1.0);
	glm::vec3 Right;
	glm::vec3 direction;
	float pitch, yaw, roll;
};

