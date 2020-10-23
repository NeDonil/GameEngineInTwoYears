#include "Engine.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "glm/gtc/type_ptr.hpp"
#include "GLAD/glad.h"
#include "Engine/ImGui/ImGuiLayer.h"
#include "Sandbox2D.h"

class Sandbox : public Engine::Application
{
public:
	Sandbox()
		: Application("Sandbox")
	{

		
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

		
	}
};
Engine::Application* Engine::CreateApplication()
{

	
	return new Sandbox();
}