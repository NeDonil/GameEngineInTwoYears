#include "Sandbox2D.h"
#include "Engine/Core/EntryPoint.h"

Sandbox2D::Sandbox2D():
	Layer("Layer2D"), m_CameraController((float)1280 / 720)
{

}

void Sandbox2D::OnAttach()
{
	m_SquareVA = Engine::VertexArray::Create();

	float SquareVertices[] = {  -0.5f, -0.5f, 0.0f, 
								-0.5f,  0.5f, 0.0f, 
								 0.5f,  0.5f, 0.0f, 
								 0.5f, -0.5f, 0.0f};

	Engine::Ref<Engine::VertexBuffer> squareVB;
	squareVB = Engine::VertexBuffer::Create(SquareVertices, sizeof(SquareVertices));
	squareVB->SetLayout({
		{Engine::ShaderDataType::Float3, "a_Position"}
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t SquareIndices[] = { 0, 1, 2, 2, 0, 3 };
	Engine::Ref<Engine::IndexBuffer> squareIB;
	squareIB = Engine::IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(uint32_t));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_Shader = Engine::Shader::Create("assets/shaders/Square.glsl");

}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Engine::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Engine::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	Engine::RenderCommand::Clear();

	Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Engine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8, 0.8 }, { 0.8, 0.2, 0.3f, 1.0f });
	Engine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5, 0.75 }, m_SquareColor);
	Engine::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Engine::Event& e)
{
	m_CameraController.OnEvent(e);
}
