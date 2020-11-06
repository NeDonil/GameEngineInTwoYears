#include "Engine.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "glm/gtc/type_ptr.hpp"
#include "GLAD/glad.h"
#include "Engine/ImGui/ImGuiLayer.h"
#include "Sandbox2D.h"

class SandboxApplication : public Engine::Application
{
public:
	SandboxApplication()
		: Application("Sandbox")
	{


		PushLayer(new Sandbox::Sandbox2D());
	}

	~SandboxApplication()
	{


	}
};

Engine::Application* Engine::CreateApplication()
{


	return new SandboxApplication();
}
