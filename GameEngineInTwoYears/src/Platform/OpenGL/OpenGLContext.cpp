#include <enpch.h>
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include "GLAD/glad.h"

namespace Engine
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) :
		m_WindowHandle(windowHandle)
	{
		ENGINE_CORE_ASSERT(windowHandle, "Handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ENGINE_CORE_ASSERT(status, "Failed to initialize Glad!");

		ENGINE_CORE_INFO("OpenGL Renderer: {0}", glGetString(GL_VENDOR));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}