#pragma once

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "Events/Event.h"

class Game;

class Window
{
public:
	Window() = default;
	static void Init(const std::string& title, int width, int height, Game* game);

	using EventCallbackFn = std::function<void(Event&)>;
	static Window* Get()
	{
		return s_Instance;
	}
	GLFWwindow* GetWindow() { return s_Instance->s_Window; }
	int GetWidth() { return s_Instance->s_Width; }
	int GetHeight() { return s_Instance->s_Height; }
	void SetHeight();
	void SetWidth();
	void SetVsync(bool b) { m_VSync = b; }
	void Update();

	struct WindowData
	{
		std::string Title;
		unsigned int width, height;
		bool Vsync;
		Game* game;
		Camera* camera;
		GLFWwindow* window;
		EventCallbackFn EventCallback;
	};
public:
	static Window* s_Instance;
	int s_Width, s_Height;
	std::string s_Title;
	GLFWwindow* s_Window;
	bool m_VSync;
	Game* s_Game;

	WindowData m_Data;
};

