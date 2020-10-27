#pragma once

#include <Engine/Core/Core.h>
#include <Engine/Scene/Scene.h>

#include <Engine/Scene/Entity.h>
#include <Engine/Scene/Components.h>

#include <imgui.h>

namespace Engine
{

	class SceneHierarchyPanel
	{
	public:

		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();

		void DrawEntityNode(Entity entity);

	private:
		Ref<Scene> m_Context;
		Entity m_SelectionEntity;
	};

}