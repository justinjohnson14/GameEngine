#include "Game.h"

#include "glm/gtc/matrix_transform.hpp"
#include "GameObject.h"
#include "Model.h"
#include <memory>

#include "Window.h"


Mesh* m_Mesh;
Mesh* m_Mesh2;
Mesh* m_Mesh3;
Mesh* m_Mesh4;
Mesh* m_Mesh5;
Mesh* m_Mesh6;
std::vector<Mesh> meshes;

std::vector<GameObject*> gameObjects;

Game::Game() : Layer("Game")
{
	
}
void Game::Init()
{
	m_Shader = new Shader("src/resources/shaders/Test.glsl");


	se = new ScriptEngine();
	Script* script = new Script("src/resources/scripts/Test.lua");
	se->AddScript(script);

	m_Mesh = new Mesh(glm::vec3(1,1,1), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), m_Shader);
	m_Mesh3 = new Mesh(glm::vec3(1,1,1), glm::vec3(1, 0, 0), glm::vec3(0, 0, 0), m_Shader);
	m_Mesh4 = new Mesh(glm::vec3(1,1,1), glm::vec3(1, 1, 0), glm::vec3(0, 0, 0), m_Shader);
	m_Mesh5 = new Mesh(glm::vec3(1,1,1), glm::vec3(1, 0, 1), glm::vec3(0, 0, 0), m_Shader);
	m_Mesh2 = new Mesh(glm::vec3(1,1,1), glm::vec3(-2, -2, -2), glm::vec3(0, 0, 0), m_Shader);
	m_Mesh6 = new Mesh(glm::vec3(1,2.0,1), glm::vec3(2, 0, 0), glm::vec3(0, 0, 0), m_Shader);
	std::shared_ptr<Model> model = std::make_unique<Model>(Model("src/resources/models/backpack/backpack.obj"));
	//Model* model2 = new Model("src/resources/models/backpack/backpack.obj");
	for (auto mesh : model->GetMeshes())
	{
		meshes.push_back(mesh);
	}

	//for (auto mesh : model2->GetMeshes())
	{
		//meshes.push_back(mesh);
	}
	//meshes = { m_Mesh, m_Mesh2, m_Mesh3, m_Mesh4, m_Mesh5, m_Mesh6 };
	//meshes.push_back(*m_Mesh2);

	SetProjectionMatrix(Window::Get()->GetWidth(), Window::Get()->GetHeight());
}

void Game::SetColor(const glm::vec4& color)
{
}

void Game::SetProjectionMatrix(float width, float height)
{
	m_Projection = glm::perspective(glm::radians(60.0f), (float)width/height, 0.1f, 100.0f);
	m_Shader->SetMat4("u_Projection", m_Projection);
}

glm::mat4 Game::GetProjectionMatrix()
{
	return m_Projection;
}

bool Game::MouseButtonEvent(int button, int action, int mods)
{
	glfwSetInputMode(Window::Get()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return true;
}

void Game::Input()
{
	m_Mesh2->SetVelocity(glm::vec3(0.0, 0.0, 0.0));
	const float cameraSpeed = 0.05f * .10f;

	if (glfwGetKey(Window::Get()->GetWindow(), GLFW_KEY_UP) == GLFW_PRESS)
		m_Mesh2->SetVelocity(glm::vec3(0, 0, -0.05f));
	if (glfwGetKey(Window::Get()->GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
		m_Mesh2->SetVelocity(glm::vec3(0, 0, 0.05f));

	if (glfwGetKey(Window::Get()->GetWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
		m_Mesh2->SetVelocity(glm::vec3(0.05f, 0, 0));
	if (glfwGetKey(Window::Get()->GetWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
		m_Mesh2->SetVelocity(glm::vec3(-0.05f, 0, 0));

	if (glfwGetKey(Window::Get()->GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
		camera->Move(FORWARD);
	if (glfwGetKey(Window::Get()->GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
		camera->Move(BACKWARD);

	if (glfwGetKey(Window::Get()->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
		camera->Move(RIGHT);
	if (glfwGetKey(Window::Get()->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
		camera->Move(LEFT);

	if (glfwGetKey(Window::Get()->GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
		camera->Move(UP);
	if (glfwGetKey(Window::Get()->GetWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera->Move(DOWN);
}

void Game::SetRotation(const glm::vec3& rot)
{
	for (auto mesh : meshes)
	{
		mesh.SetRotation(rot);
	}
}

void Game::Update(double delta)
{
	for (auto mesh : meshes)
	{
		//m_Shader->SetMat4("u_View", m_View);
		mesh.Update();
	}

	m_Time = glfwGetTime();

	/*for (auto script : se->GetScripts())
	{
		script->FixedUpdate();
	}*/
}

void Game::Render(double lag)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for(auto mesh : meshes)
	{
		mesh.GetShader()->Bind();
		mesh.GetShader()->UploadUniformMat4("u_Projection", m_Projection);
		mesh.Render(camera);	
	}

	/*for (auto gameObject : gameObjects)
	{
		//gameObject->BindShader();
		//gameObject->Render();
	}

	for (auto script : se->GetScripts())
	{
		//script->Update();
	}*/

}