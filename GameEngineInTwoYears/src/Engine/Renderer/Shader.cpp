#include <enpch.h>

#include "Shader.h"
#include "Renderer.h"
#include <Engine/Platform/OpenGL/OpenGLShader.h>

namespace Engine
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: ENGINE_CORE_ASSERT(false, "Engine is not supported None API");
			case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		ENGINE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}