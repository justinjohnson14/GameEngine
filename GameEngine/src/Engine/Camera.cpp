#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

Camera::Camera(const glm::vec3& pos, const glm::vec3& rot)
	: m_Position(pos), m_Rotation(rot)
{
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	yaw = -90.0f;
	pitch = 0.0f;
}

void Camera::Move(Camera_Movement direction)
{
	float velocity = (float)0.05 * (float)0.10;

	if (direction == FORWARD)
		m_Position += cameraFront * velocity;
	if (direction == BACKWARD)
		m_Position -= cameraFront * velocity;
	if (direction == LEFT)
		m_Position -= Right * velocity;
	if (direction == RIGHT)
		m_Position += Right * velocity;
	if (direction == UP)
		m_Position.y += 1 * velocity;
	if (direction == DOWN)
		m_Position.y -= 1 * velocity;
}

void Camera::Rotate(const glm::vec3& rot)
{
	
}

glm::mat4 Camera::GetViewMatrix() 
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
	// also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(cameraFront, glm::vec3(0,1,0)));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	cameraUp = glm::normalize(glm::cross(Right, cameraFront));
	m_View = glm::lookAt(m_Position, m_Position + cameraFront, cameraUp);
	return m_View;
}
