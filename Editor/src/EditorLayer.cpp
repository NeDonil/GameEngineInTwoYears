#include <chrono>
#include "EditorLayer.h"
#include "Engine/Core/EntryPoint.h"

#define ENABLE_PROFILING

EditorLayer::EditorLayer():
	Layer("Layer2D"), m_CameraController((float)1280 / 720, true)
{
#ifdef ENABLE_PROFILING
	ENGINE_PROFILE_FUNCTION();
#endif
}

void EditorLayer::OnAttach()
{
#ifdef ENABLE_PROFILING
	ENGINE_PROFILE_FUNCTION();
#endif
	m_CheckerboardTexture = Engine::Texture2D::Create("assets/textures/clown.png");

	Engine::FramebufferSpecification fbSpec;

	fbSpec.Width = 1280;
	fbSpec.Height = 720;

	m_Framebuffer = Engine::Framebuffer::Create(fbSpec);
	m_Framebuffer->Bind();
}

void EditorLayer::OnDetach()
{
#ifdef ENABLE_PROFILING
	ENGINE_PROFILE_FUNCTION();
#endif
}

void EditorLayer::OnUpdate(Engine::Timestep ts)
{
#ifdef ENABLE_PROFILING
	ENGINE_PROFILE_FUNCTION();
#endif

	{
		ENGINE_PROFILE_SCOPE("EditorLayer::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	Engine::Renderer2D::ResetStats();
	{
		m_Framebuffer->Bind();
		ENGINE_PROFILE_SCOPE("EditorLayer::Renderer prep");
		Engine::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		Engine::RenderCommand::Clear();
	}

	{
		ENGINE_PROFILE_SCOPE("EditorLayer::Renderer draw");
		Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Engine::Renderer2D::DrawQuad({ 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }, {0.2f, 0.5f, 0.8f, 1.0f});
		Engine::Renderer2D::DrawQuad({ 0.0f, -2.0f, 1.0f }, { 1.0f, 1.0f }, { 0.5f, 0.2f, 0.8f, 1.0f });

		Engine::Renderer2D::DrawQuad({ 2.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }, m_CheckerboardTexture);
		Engine::Renderer2D::DrawQuad({ 2.0f, -2.0f, 1.0f }, { 1.0f, 1.0f }, m_CheckerboardTexture);

		Engine::Renderer2D::EndScene();

		m_Framebuffer->Unbind();
	}
}

void EditorLayer::OnImGuiRender()
{
#ifdef ENABLE_PROFILING
	ENGINE_PROFILE_FUNCTION();
#endif

	static bool dockingEnabled = true;
	if (dockingEnabled)
	{
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
			ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("Exit")) Engine::Application::Get().Close();
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}

			ImGui::Begin("Settings");
				auto stats = Engine::Renderer2D::GetStats();
				ImGui::Text("Renderer2D Stats:");
				ImGui::Text("Draw Calls: %d", stats.DrawCalls);
				ImGui::Text("Quads: %d", stats.QuadCount);
				ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
				ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
			ImGui::End();

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
			ImGui::Begin("Viewport");
			ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
			if (m_ViewportSize != *((glm::vec2*) & viewportPanelSize))
			{
				m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
				m_Framebuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);

				m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
			}
			uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
			ImGui::Image((void*)textureID, ImVec2{ viewportPanelSize.x, viewportPanelSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
			ImGui::End();
			ImGui::PopStyleVar();

		ImGui::End();
	}

	else
	{
		ImGui::Begin("Settings");

		auto stats = Engine::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

		uint32_t textureID = m_CheckerboardTexture->GetRendererID();
		ImGui::Image((void*)textureID, ImVec2{ 1280, 720.0f }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
	}
}

void EditorLayer::OnEvent(Engine::Event& e)
{
#ifdef ENABLE_PROFILING
	ENGINE_PROFILE_FUNCTION();
#endif
	m_CameraController.OnEvent(e);
}
