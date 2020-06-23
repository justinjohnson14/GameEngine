#include "ImguiLayer.h"

#include "imgui/imgui-master/imgui.h"
#include "imgui/imgui-master/examples/imgui_impl_glfw.h"
#include "imgui/imgui-master/examples/imgui_impl_opengl3.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Window.h"

glm::vec4 color(0);

ImguiLayer::ImguiLayer(Game* game) : Layer("ImguiLayer"), m_Game(game)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	/*if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}*/

	//GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(Window::Get()->GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 410");
}

void ImguiLayer::Input()
{

}

void ImguiLayer::Update(double lag)
{

}

bool ImguiLayer::MouseButtonEvent(int button, int action, int mods)
{
	ImGuiIO& io = ImGui::GetIO();
	if (m_Clicked)
	{
		return true;
	}
	else
	{
		return false;
	}
}

glm::vec3 rotation = glm::vec3(0.0);

void ImguiLayer::Render(double lag)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowMetricsWindow();

	bool show = false;
	ImGui::Begin("New Tool", &show, ImGuiWindowFlags_MenuBar);
	//ImGui::ColorEdit4("Shape Color", glm::value_ptr(color));
	ImGui::SliderFloat("X Rotation", &rotation.x, 0, 360, nullptr, 1.0f);
	ImGui::SliderFloat("Y Rotation", &rotation.y, 0, 360, nullptr, 1.0f);
	ImGui::SliderFloat("Z Rotation", &rotation.z, 0, 360, nullptr, 1.0f);
	ImGui::End();

	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2((float)Window::Get()->GetWidth(), (float)Window::Get()->GetHeight());
	//m_Clicked = io.MouseClicked;
	m_Clicked = io.WantCaptureMouse;

	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	m_Game->SetRotation(rotation);

	//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	//{
	//	GLFWwindow* backup_current_context = glfwGetCurrentContext();
	//	ImGui::UpdatePlatformWindows();
	//	ImGui::RenderPlatformWindowsDefault();
	//	glfwMakeContextCurrent(backup_current_context);
	//}
}
