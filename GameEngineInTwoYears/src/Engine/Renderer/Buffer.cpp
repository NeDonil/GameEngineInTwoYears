#include <enpch.h>
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Engine
{
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: ENGINE_CORE_ASSERT(false, "RendererAPI:None is not supported now"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		ENGINE_CORE_ASSERT(false, "Unknown RendereAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: ENGINE_CORE_ASSERT(false, "RendererAPI:None is not supported now"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(indices, size);
		}

		ENGINE_CORE_ASSERT(false, "Unknown RendereAPI!");
		return nullptr;
	}
}