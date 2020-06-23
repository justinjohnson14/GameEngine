#pragma once

#include <Windows.h>

#include "Window.h"
#include "Game.h"
#include "Renderer.h"
#include "Layer.h"
#include "ImguiLayer.h"

#include <vector>

class Application
{
public:
	Application(const std::string&, int, int, bool, Game*);
	void Loop();
	void Input();
	void Update(double);
	void Render(double);
private:
	Window* m_Window;
	Game* gameLayer = new Game();
	ImguiLayer* imguiLayer;
	Game* m_Game;
	std::vector<Layer*> layers;
};

