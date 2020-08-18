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
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
	}
};
Engine::Application* Engine::CreateApplication()
{
#ifdef ENABLE_PROFILING
	ENGINE_PROFILE_FUNCTION();
#endif
	return new Sandbox();
}