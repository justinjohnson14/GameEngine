#include "Window.h"
#include "Core.h"

#include "Game.h"
#include "Log.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/EventManager.h"

bool wireframe = false;
bool fullscreen = false;

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void FrameBufferResize(GLFWwindow* window, int width, int height);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void CursPosCallback(GLFWwindow* window, double xpos, double ypos);

Window* Window::s_Instance = new Window();

void Window::Init(const std::string& title, int width, int height, Game* game)
{
	s_Instance->s_Title = std::string(title);
	s_Instance->s_Width = width;
	s_Instance->s_Height = height;
	s_Instance->s_Game = game;
	if (!glfwInit())
		ENGINE_LOG_ERROR("Error initializing GLFW!");

	s_Instance->s_Window = glfwCreateWindow(s_Instance->s_Width, s_Instance->s_Height, s_Instance->s_Title.c_str(), nullptr, nullptr);

	if (!s_Instance->s_Window)
	{
		ENGINE_LOG_ERROR("Error creating window!");
		glfwTerminate();
	}

	s_Instance->m_Data.Title = s_Instance->s_Title;
	s_Instance->m_Data.width = s_Instance->s_Width;
	s_Instance->m_Data.height = s_Instance->s_Height;
	s_Instance->m_Data.game = s_Instance->s_Game;
	s_Instance->m_Data.camera = s_Instance->s_Game->camera;
	s_Instance->m_Data.window = s_Instance->s_Window;

	glfwSetWindowUserPointer(s_Instance->s_Window, &s_Instance->m_Data);

	glfwSetKeyCallback(s_Instance->s_Window, KeyCallback);

	glfwSetWindowSizeCallback(s_Instance->s_Window, FrameBufferResize);

	glfwSetMouseButtonCallback(s_Instance->s_Window, MouseButtonCallback);

	glfwSetCursorPosCallback(s_Instance->s_Window, CursPosCallback);

	glfwMakeContextCurrent(s_Instance->s_Window);

	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GL_MAJOR_VERSION, 3);
	glfwWindowHint(GL_MINOR_VERSION, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(s_Instance->s_Window, (vidmode->width - width) / 2, (vidmode->height - height) / 2);
}

void Window::Update()
{
	glfwSwapBuffers(s_Instance->s_Window);
	glfwPollEvents();
	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(s_Instance->s_Window);
	s_Instance->s_Width = data.width;
	s_Instance->s_Height = data.height;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window::WindowData& data = *(Window::WindowData*)glfwGetWindowUserPointer(window);
	switch (action)
	{
	case GLFW_PRESS:
	{
		KeyTypedEvent* e = new KeyTypedEvent(key, scancode, action, mods, false);
		EventManager::Get()->Push(e);
		break;
	}
	case GLFW_RELEASE:
	{
		KeyReleasedEvent* e = new KeyReleasedEvent(key, scancode, action, mods, false);
		EventManager::Get()->Push(e);
		break;
	}
	case GLFW_REPEAT:
	{
		KeyTypedEvent* e = new KeyTypedEvent(key, scancode, action, mods, true);
		EventManager::Get()->Push(e);
		break;
	}
	default:
		break;
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
		glfwSetWindowShouldClose(data.window, true);

	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		wireframe = !wireframe;
		if (wireframe == true)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		fullscreen = !fullscreen;
		if (fullscreen)
		{
			glfwSetWindowMonitor(data.window, glfwGetPrimaryMonitor(), 0, 0, 1920, 1080, 60);
		}
		else
		{
			glfwSetWindowMonitor(data.window, NULL, 0, 0, 800, 600, 60);
			glfwWindowHint(GLFW_DECORATED, GL_TRUE);
		}
	}
}

void FrameBufferResize(GLFWwindow* window, int width, int height)
{
	Window::WindowData& data = *(Window::WindowData*)glfwGetWindowUserPointer(window);
	data.width = width;
	data.height = height;

	//WindowResizeEvent event((unsigned int)width, (unsigned int)height);
	//data.EventCallback(event);

	glViewport(0, 0, width, height);

	ENGINE_LOG_INFO("Window demensions: {0},{1}", width, height);

	data.game->SetProjectionMatrix((float)width, (float)height);
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	Window::WindowData& data = *(Window::WindowData*)glfwGetWindowUserPointer(window);

	MouseButtonEvent* e = new MouseButtonEvent(button, action, mods);
	EventManager::Get()->Push(e);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

bool firstMouse = true;
double lastX, lastY;

void CursPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
	{
		Window::WindowData& data = *(Window::WindowData*)glfwGetWindowUserPointer(window);
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		double xoffset = xpos - lastX;
		double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
		lastX = xpos;
		lastY = ypos;

		float sensitivity = 0.1f; // change this value to your liking
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		data.camera->yaw += (float)xoffset;
		data.camera->pitch += (float)yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (data.camera->pitch > 89.0f)
			data.camera->pitch = 89.0f;
		if (data.camera->pitch < -89.0f)
			data.camera->pitch = -89.0f;

		//std::cout << "Mouse position: (" << xoffset << ", " << yoffset << ")\n";

		data.camera->cameraFront.x = cos(glm::radians(data.camera->yaw)) * cos(glm::radians(data.camera->pitch));
		//data.camera->cameraFront.y = sin(glm::radians(data.camera->pitch));
		data.camera->cameraFront.z = sin(glm::radians(data.camera->yaw)) * cos(glm::radians(data.camera->pitch));
		data.camera->cameraFront = glm::normalize(data.camera->cameraFront);
	}
}
