#pragma once
#include "Engine.h"
#include <vector>
#include <glm/glm.hpp>
#include "Panels/SceneHierarchyPanel.h"

#include "Engine/Scene/SceneSerializer.h"

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
		Ref<SceneHierarchyPanel> m_Panel;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;
		Ref<SceneSerializer> m_Serializer;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize;

		struct ProfileResult {
			const char* Name;
			float Time;
		};

	};
}