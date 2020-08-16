#include "Engine.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "glm/gtc/type_ptr.hpp"
#include "GLAD/glad.h"
#include "Engine/ImGui/ImGuiLayer.h"
#include "EditorLayer.h"

class Editor : public Engine::Application
{
public:
	Editor()
		:Application("Editor")
	{
		PushLayer(new EditorLayer());
	}

	~Editor()
	{
	}
};
Engine::Application* Engine::CreateApplication()
{
	return new Editor();
}