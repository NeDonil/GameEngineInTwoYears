#include "enpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Engine {

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    ENGINE_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(width, height);
		}

		ENGINE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    ENGINE_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(path);
		}

		ENGINE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}