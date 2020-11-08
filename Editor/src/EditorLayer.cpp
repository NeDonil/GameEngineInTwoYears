#include <chrono>
#include "EditorLayer.h"
#include "Engine/Core/EntryPoint.h"
#include "Engine/Core/Application.h"
#include "Engine/Core/Core.h"

#include "entt.hpp"

float frameTime = 0.0f;

namespace Engine
{
	EditorLayer::EditorLayer() :
		Layer("Layer2D")
	{
	}

	void EditorLayer::OnAttach()
	{
		RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });

		FramebufferSpecification fbSpec;

		fbSpec.Width = 1280;
		fbSpec.Height = 720;

		m_Framebuffer = Framebuffer::Create(fbSpec);

		m_ActiveScene = CreateRef<Scene>();
		m_HierarchyPanel = CreateRef<SceneHierarchyPanel>(m_ActiveScene);

#ifdef NativeScriptExample 
		// rest in peace
		class CameraController : public ScriptableEntity
		{
		public:
			void OnCreate()
			{
			}

			void OnDestroy()
			{
			}

			void OnUpdate(Timestep ts)
			{
				auto& translation = GetComponent<TransformComponent>().Translation;

				float speed = 5.0f;

				if (Input::IsKeyPressed(ENGINE_KEY_A))
					translation.x -= speed * ts;
				else if (Input::IsKeyPressed(ENGINE_KEY_D))
					translation.x += speed * ts;

				if (Input::IsKeyPressed(ENGINE_KEY_W))
					translation.y += speed * ts;
				else if (Input::IsKeyPressed(ENGINE_KEY_S))
					translation.y -= speed * ts;
			}
		};
#endif

	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		ENGINE_PROFILE_SCOPE("EditorLayer::OnUpdate");

		if (FramebufferSpecification spec = m_Framebuffer->GetSpecification();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f &&
			(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);

			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}

		Renderer2D::ResetStats();
		m_Framebuffer->Bind();

		RenderCommand::Clear();

		m_ActiveScene->OnUpdate(ts);

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
				if (ImGui::MenuItem("New", "Ctrl+N"))
					NewScene();

				if (ImGui::MenuItem("Open...", "Ctrl+O"))
					OpenScene();

				if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
					SaveSceneAs();

				if (ImGui::MenuItem("Exit")) 
					Application::Get().Close();

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		m_HierarchyPanel->OnImGuiRender();

		ImGui::Begin("Settings");
		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Frame Render Time: %0.3fms", frameTime);
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());


		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
		ImGui::Begin("Viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ viewportPanelSize.x, viewportPanelSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(ENGINE_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		bool control = Input::IsKeyPressed(ENGINE_KEY_LEFT_CONTROL) || Input::IsKeyPressed(ENGINE_KEY_RIGHT_CONTROL);
		bool shift = Input::IsKeyPressed(ENGINE_KEY_LEFT_SHIFT) || Input::IsKeyPressed(ENGINE_KEY_RIGHT_SHIFT);

		if (e.GetRepeatCount() > 0)
			return false;

		switch (e.GetKeyCode())
		{

			case ENGINE_KEY_S:
			{
				if (control && shift)
					SaveSceneAs();
			} break;

			case ENGINE_KEY_N:
			{
				if (control)
					NewScene();
			} break;

			case ENGINE_KEY_O:
			{
				if (control)
					OpenScene();
			} break;

		}
	}

	void EditorLayer::SaveSceneAs()
	{
		std::string filepath = FileDialog::SaveFile("Engine Scene (*.scene)\0*.scene\0");
		if (!filepath.empty())
		{
			SceneSerializer serializer(m_ActiveScene);
			serializer.Serialize(filepath);
		}
	}

	void EditorLayer::NewScene()
	{
		m_ActiveScene = CreateRef<Scene>();
		m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		m_HierarchyPanel->SetContext(m_ActiveScene);
	}

	void EditorLayer::OpenScene()
	{
		std::string filepath = FileDialog::OpenFile("Engine Scene (*.scene)\0*.scene\0");
		if (!filepath.empty())
		{
			m_ActiveScene = CreateRef<Scene>();
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_HierarchyPanel->SetContext(m_ActiveScene);

			SceneSerializer serializer(m_ActiveScene);
			serializer.Deserialize(filepath);
		}
	}

}