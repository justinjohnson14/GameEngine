#pragma once

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct WindowData
{
	std::string Title;
	unsigned int width, height;
	bool Vsync;
};

class Window
{
public:
	Window(const std::string&, int, int);

	GLFWwindow* GetWindow();
	int GetWidth() { return m_Width; }
	int GetHeight() { return m_Height; }
private:
	int m_Width, m_Height;
	std::string m_Title;
	GLFWwindow* m_Window;

	WindowData m_Data;
};

