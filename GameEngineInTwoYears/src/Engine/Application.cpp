#include "enpch.h"
#include "GLFW/glfw3.h"
#include "Application.h"
#include "Event/ApplicationEvent.h"
#include "Log.h"
#include "Input.h"

#include <GLAD/glad.h>

namespace Engine
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		ENGINE_CORE_ASSERT(s_Instance, "Applicaiton is already exists");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[] = { -0.5f, -0.5f, 0.0f,
					          0.5f, -0.5f, 0.0f,
					          0.0f,  0.5f, 0.0f };

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		m_VertexBuffer->Bind();

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

		unsigned int indices[] = { 0, 1, 2 };

		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_IndexBuffer->Bind();

		std::string vertex = R"(
			#version 330 core
			layout (location = 0) in vec3 pos;
			
			void main()
			{
				gl_Position = vec4(pos, 1.0f);
			}		
		)";

		std::string fragment = R"(
			#version 330 core
			
			void main()
			{
				gl_FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
			}		
		)";

		m_Shader.reset(new Shader(vertex, fragment));
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		ENGINE_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();

		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}