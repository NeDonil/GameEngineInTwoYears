#include "Engine.h"
#include "Engine/Platform/OpenGL/OpenGLShader.h"
#include "glm/gtc/type_ptr.hpp"
#include "GLAD/glad.h"
#include "imgui.h"

class ExampleLayer : public Engine::Layer
{
public:
	ExampleLayer() :
		Layer("Example"), m_Camera(-1.6, 1.6f, -0.9, 0.9), m_CameraPosition(glm::vec3(0.0f)), m_SquarePosition(glm::vec3(1.0f))
	{
		m_VertexArray.reset(Engine::VertexArray::Create());

		float vertices[] = { -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
							  0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
							  0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f }; 

		Engine::Ref<Engine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));

		Engine::BufferLayout layout = {
			{Engine::ShaderDataType::Float3, "a_Position"},
			{Engine::ShaderDataType::Float4, "a_Color"},
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[] = { 0, 1, 2 };
		Engine::Ref<Engine::IndexBuffer> indexBuffer;
		indexBuffer.reset(Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);
		//---------------------------------------------------------------------------------------------
		m_SquareVA.reset(Engine::VertexArray::Create());

		float SquareVertices[] = {	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
									-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
									 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
									 0.5f, -0.5f, 0.0f, 1.0f, 0.0f };
		Engine::Ref<Engine::VertexBuffer> squareVB;
		squareVB.reset(Engine::VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));
		squareVB->SetLayout({
			{Engine::ShaderDataType::Float3, "a_Position"},
			{Engine::ShaderDataType::Float2, "a_TexCoord"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t SquareIndices[] = { 0, 1, 2, 2, 0, 3 };
		Engine::Ref<Engine::IndexBuffer> squareIB;
		squareIB.reset(Engine::IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertex = R"(
			#version 330 core
			layout (location = 0) in vec3 a_Position;
			layout (location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color; 
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
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

		m_Shader.reset(Engine::Shader::Create(vertex, fragment));

		std::string vertexSquare = R"(
			#version 330 core
			layout (location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
			}		
		)";

		std::string fragmentSquare = R"(
			#version 330 core

			uniform vec3 u_Color;

			void main()
			{
				gl_FragColor = vec4(u_Color, 1.0f);
			}		
		)";

		m_FlatColorShader.reset(Engine::Shader::Create(vertexSquare, fragmentSquare));

		m_TextureShader.reset(Engine::Shader::Create("assets/shaders/Texture.glsl"));
		m_Texture = Engine::Texture2D::Create("assets/textures/Checkerboard.png");
		m_AlsoTexture = Engine::Texture2D::Create("assets/textures/icon.png");

		std::dynamic_pointer_cast<Engine::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Engine::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Engine::Timestep ts) override
	{
		if (Engine::Input::IsKeyPressed(ENGINE_KEY_W))
			m_CameraPosition.y += m_CameraSpeed * (float) ts;
		else if (Engine::Input::IsKeyPressed(ENGINE_KEY_S))
			m_CameraPosition.y -= m_CameraSpeed * (float)ts;
		if (Engine::Input::IsKeyPressed(ENGINE_KEY_A))
			m_CameraPosition.x -= m_CameraSpeed * (float)ts;
		else if (Engine::Input::IsKeyPressed(ENGINE_KEY_D))
			m_CameraPosition.x += m_CameraSpeed * (float)ts;

		Engine::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		Engine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);

		Engine::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1));

		std::dynamic_pointer_cast<Engine::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Engine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				glm::vec3 pos(0.11 * i, 0.11 * j, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos + m_SquarePosition);
				Engine::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform * scale);
			}
		}

		//Engine::Renderer::Submit(m_Shader, m_VertexArray);
		m_Texture->Bind();
		Engine::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_AlsoTexture->Bind();
		Engine::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(0.33f)));

		Engine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square color", glm::value_ptr(m_SquareColor));
		ImGui::SliderFloat3("Position", glm::value_ptr(m_SquarePosition), -2.0f, 2.0f);
		ImGui::End();
	}

	void OnEvent(Engine::Event& event) override
	{
		
	}

private:
	Engine::Ref<Engine::Shader> m_Shader;
	Engine::Ref<Engine::VertexArray> m_VertexArray;

	Engine::Ref<Engine::Shader> m_FlatColorShader, m_TextureShader;
	Engine::Ref<Engine::VertexArray> m_SquareVA;

	Engine::Ref<Engine::Texture2D> m_Texture, m_AlsoTexture;

	Engine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 5.0f;
	float m_SquareSpeed = 1.0f;
	glm::vec3 m_SquarePosition;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Engine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};
Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}