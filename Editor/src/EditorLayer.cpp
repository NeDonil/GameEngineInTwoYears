#include <chrono>
#include "EditorLayer.h"
#include "Engine/Core/EntryPoint.h"
#include "Engine/Core/Application.h"

#include "entt.hpp"

float frameTime = 0.0f;

namespace Engine
{
	EditorLayer::EditorLayer() :
		Layer("Layer2D"), m_CameraController((float)1280 / 720, true)
	{
	}

	void EditorLayer::OnAttach()
	{
		m_CheckerboardTexture = Texture2D::Create("assets/textures/clown.png");

		FramebufferSpecification fbSpec;

		fbSpec.Width = 1280;
		fbSpec.Height = 720;

		m_Framebuffer = Framebuffer::Create(fbSpec);

		m_ActiveScene = CreateRef<Scene>();

		m_SquareEntity = m_ActiveScene->CreateEntity("Orange Square");
		m_SquareEntity.AddComponent<SpriteRendererComponent>(glm::vec4( 8.0f, 0.5f, 0.2f, 1.0f ));
		m_SquareEntity.GetComponent<TransformComponent>().Transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

		RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		ENGINE_PROFILE_SCOPE("EditorLayer::OnUpdate");

		if (m_ViewportFocused)
			m_CameraController.OnUpdate(ts);
		

		Renderer2D::ResetStats();
		m_Framebuffer->Bind();
		
		RenderCommand::Clear();
	
		Renderer2D::BeginScene(m_CameraController.GetCamera());

		m_ActiveScene->OnUpdate(ts);

		Renderer2D::EndScene();
		m_Framebuffer->Unbind();

		frameTime = (float)ts;
	}

	void EditorLayer::OnImGuiRender()
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
				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");
		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Frame Render Time: %0.3fms", frameTime);
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		if (m_SquareEntity)
		{
				ImGui::Separator();

				std::string& tag = m_SquareEntity.GetComponent<TagComponent>().Tag;
				ImGui::Text("%s", tag.c_str());

				glm::vec4& squareColor = m_SquareEntity.GetComponent<SpriteRendererComponent>().Color;
				ImGui::ColorEdit4("Color", glm::value_ptr(squareColor));

				ImGui::Separator();
		}
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
		ImGui::Begin("Viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if (m_ViewportSize != *((glm::vec2*) & viewportPanelSize) && viewportPanelSize.x > 0 && viewportPanelSize.y > 0 ) 
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

	void EditorLayer::OnEvent(Event& e)
	{
		m_CameraController.OnEvent(e);
	}
}