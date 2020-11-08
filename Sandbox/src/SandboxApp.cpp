#include "Engine.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "glm/gtc/type_ptr.hpp"
#include "GLAD/glad.h"
#include "Engine/ImGui/ImGuiLayer.h"
#include "Sandbox2D.h"
#include "TestScene.h"

class SandboxApplication : public Engine::Application
{
public:
	SandboxApplication()
		: Application("Sandbox")
	{
		PushLayer(new TestSceneLayer());
	}

	~SandboxApplication()
	{


	}
};

Engine::Application* Engine::CreateApplication()
{


	return new SandboxApplication();
}
