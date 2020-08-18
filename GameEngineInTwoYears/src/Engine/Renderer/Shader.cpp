#include <enpch.h>

#include "Shader.h"
#include "Renderer.h"
#include <Platform/OpenGL/OpenGLShader.h>

namespace Engine
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		switch (Renderer::GetAPI())
		{

			case RendererAPI::API::None: ENGINE_CORE_ASSERT(false, "Engine is not supported None API");
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filepath);
		}

		ENGINE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: ENGINE_CORE_ASSERT(false, "Engine is not supported None API");
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		ENGINE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		ENGINE_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		ENGINE_CORE_ASSERT(Exists(shader), "Shader not found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name)
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		return m_Shaders.find(name) != m_Shaders.end();
	}

}