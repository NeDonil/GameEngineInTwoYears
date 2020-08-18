#include <enpch.h>
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Engine
{
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: ENGINE_CORE_ASSERT(false, "RendererAPI:None is not supported now"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		ENGINE_CORE_ASSERT(false, "Unknown RendereAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: ENGINE_CORE_ASSERT(false, "RendererAPI:None is not supported now"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(size);
		}

		ENGINE_CORE_ASSERT(false, "Unknown RendereAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: ENGINE_CORE_ASSERT(false, "RendererAPI:None is not supported now"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}

		ENGINE_CORE_ASSERT(false, "Unknown RendereAPI!");
		return nullptr;
	}

}