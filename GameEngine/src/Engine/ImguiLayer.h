#pragma once

#include "Layer.h"
#include "Game.h"

class ImguiLayer : public Layer
{
public:
	ImguiLayer(Game*);
	void Update(double);
	void Input();
	void Render(double);
	bool MouseButtonEvent(int,int,int);
private:
	Game* m_Game;
	bool m_Clicked;
};

