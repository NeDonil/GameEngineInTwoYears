#pragma once
#include "Engine.h"
#include "Engine/Renderer/EditorCamera.h"
#include <vector>
#include <glm/glm.hpp>
#include "Panels/SceneHierarchyPanel.h"

#include "Engine/Scene/SceneSerializer.h"

#include "Engine/Utils/PlatformUtils.h"

#include "ImGuizmo.h"

namespace Engine
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);

		void SaveSceneAs();
		void NewScene();
		void OpenScene();
	private:
		Ref<SceneHierarchyPanel> m_SceneHierarchyPanel;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;

		EditorCamera m_EditorCamera;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = {0.0f, 0.0f};

		int m_GizmoType = -1;

		struct ProfileResult {
			const char* Name;
			float Time;
		};

	};
}