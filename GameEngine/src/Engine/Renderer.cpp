#include "Renderer.h"

#include "GL/glew.h"
#include "Log.h"
#include "Window.h"

void Renderer::Init()
{
	GLint glew = glewInit();
	if (glew != GLEW_OK)
		ENGINE_LOG_ERROR("Error creating glew instance");

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	glViewport(0, 0, Window::Get()->GetWidth(), Window::Get()->GetHeight());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}
