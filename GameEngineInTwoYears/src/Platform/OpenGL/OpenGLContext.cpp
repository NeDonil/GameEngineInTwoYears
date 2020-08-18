#include <enpch.h>
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include "GLAD/glad.h"

namespace Engine
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) :
		m_WindowHandle(windowHandle)
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		ENGINE_CORE_ASSERT(windowHandle, "Handle is null!");
	}

	void OpenGLContext::Init()
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ENGINE_CORE_ASSERT(status, "Failed to initialize Glad!");

		ENGINE_CORE_INFO("OpenGL Renderer: {0}", glGetString(GL_VENDOR));
	}

	void OpenGLContext::SwapBuffers()
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		glfwSwapBuffers(m_WindowHandle);
	}
}