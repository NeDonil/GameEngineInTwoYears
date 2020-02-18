#include <enpch.h>
#include "Buffer.h"
#include "Renderer.h"
#include <Engine/Platform/OpenGL/OpenGLBuffer.h>

namespace Engine
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: ENGINE_CORE_ASSERT(false, "RendererAPI:None is not supported now"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		ENGINE_CORE_ASSERT(false, "Unknown RendereAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: ENGINE_CORE_ASSERT(false, "RendererAPI:None is not supported now"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}

		ENGINE_CORE_ASSERT(false, "Unknown RendereAPI!");
		return nullptr;
	}
}