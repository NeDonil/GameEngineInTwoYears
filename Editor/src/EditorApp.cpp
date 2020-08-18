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
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		PushLayer(new EditorLayer());
	}

	~Editor()
	{
	}
};
Engine::Application* Engine::CreateApplication()
{
#ifdef ENABLE_PROFILING
	ENGINE_PROFILE_FUNCTION();
#endif
	return new Editor();
}