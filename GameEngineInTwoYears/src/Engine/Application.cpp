#include "enpch.h"
#include "GLFW/glfw3.h"
#include "Application.h"
#include "Event/ApplicationEvent.h"
#include "Log.h"
#include "Input.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"

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

		m_VertexArray.reset(VertexArray::Create());

		float vertices[] = { -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
							  0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
							  0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f };

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
		//---------------------------------------------------------------------------------------------
		m_SquareVA.reset(VertexArray::Create());

		float SquareVertices[] = {  -0.75f, -0.75f, 0.0f,
									-0.75f,  0.75f, 0.0f,
									 0.75f,  0.75f, 0.0f,
									 0.75f, -0.75f, 0.0f };
		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));
		squareVB->SetLayout({
			{ShaderDataType::Float3, "a_Position"}
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t SquareIndices[] = { 0, 1, 2, 2, 0, 3 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertex = R"(
			#version 330 core
			layout (location = 0) in vec3 a_Position;
			layout (location = 1) in vec4 a_Color;
			
			out vec3 v_Position;
			out vec4 v_Color; 
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0f);
			}		
		)";

		std::string fragment = R"(
			#version 330 core
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				gl_FragColor = v_Color;
			}		
		)";

		std::string vertexSquare = R"(
			#version 330 core
			layout (location = 0) in vec3 a_Position;
			
			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0f);
			}		
		)";

		std::string fragmentSquare = R"(
			#version 330 core

			void main()
			{
				gl_FragColor = vec4(0.2f, 0.8f, 0.8f, 1.0f);
			}		
		)";

		m_Shader.reset(new Shader(vertex, fragment));
		m_ShaderSquare.reset(new Shader(vertexSquare, fragmentSquare));
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
			RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
			RenderCommand::Clear();

			Renderer::BeginScene();

				m_ShaderSquare->Bind();
				Renderer::Submit(m_SquareVA);

				m_Shader->Bind();
				Renderer::Submit(m_VertexArray);

			Renderer::EndScene();

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