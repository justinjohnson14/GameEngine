#include "Application.h"
#include <Windows.h>
#include "Core.h"
#include "Log.h"
#include "Events/EventManager.h"
#include "LayerStack.h"

Application::Application(const std::string& title, int width, int height, bool vSync, Game* game)
	: m_Game(game)
{
	Window::Init(title, width, height, gameLayer);

	Log::Init();
	ENGINE_LOG_INFO("Log initialized");

	GLint glew = glewInit();
	if (glew != GLEW_OK)
		ENGINE_LOG_ERROR("Error creating glew instance");

	Renderer::Init();
	gameLayer->Init();
	imguiLayer = new ImguiLayer(gameLayer);

	LayerStack::Get()->PushStack(gameLayer);
	LayerStack::Get()->PushStack(imguiLayer);

	//game->Init(m_Window);

	Loop();
}

/*
void Application::Input()
{
	m_Game->Input();
}

void Application::Update(double delta)
{
	m_Game->Update(delta);
}

void Application::Render(double lag)
{
	m_Game->Render(lag);
	m_Window->Update();
}*/

void Application::Loop()
{

	double previous = glfwGetTime() * 1000;
	double lag = 0.0;
	double MS_PER_UPDATE = 1000/30;
	while(!glfwWindowShouldClose(m_Window->GetWindow()))
	{ 
		double current = glfwGetTime() * 1000;
		double elapsed = current - previous;
		previous = current;
		lag += elapsed;

		gameLayer->Input();

		//for (auto event : Event::GetEvents())
		{
			//event.handle;
		}

		while (lag >= MS_PER_UPDATE)
		{
			for(auto layer : LayerStack::Get()->GetStack())
			{
				layer->Update(elapsed);
			}

			while (!(EventManager::Get()->GetQueue().empty()))
			{
				Event* e = EventManager::Get()->GetQueue().front();
				e->Handle();
				EventManager::Get()->Pop();
			}
			lag -= MS_PER_UPDATE;
			
			//Update(elapsed);
			//lag -= MS_PER_UPDATE;
		}

		for(auto layer : LayerStack::Get()->GetStack())
		{
			layer->Render(lag / MS_PER_UPDATE);
		}

		m_Window->Update();
		

		//Render(lag / MS_PER_UPDATE);
	}
}
