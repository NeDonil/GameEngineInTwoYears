#include <enpch.h>
#include "VertexArray.h"
#include "Renderer.h"
#include "Engine/Platform/OpenGL/OpenGLVertexArray.h"

namespace Engine
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:  ENGINE_CORE_ASSERT(false, "RendererApi::None is currently not supported!"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}
		ENGINE_CORE_ASSERT(false, "Unknown RendereAPI!");
		return nullptr;
	}
}