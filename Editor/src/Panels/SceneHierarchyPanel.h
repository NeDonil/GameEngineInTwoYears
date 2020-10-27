#pragma once

#include <Engine/Core/Core.h>
#include <Engine/Scene/Scene.h>

#include <Engine/Scene/Entity.h>
#include <Engine/Scene/Components.h>

#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Engine
{

	class SceneHierarchyPanel
	{
	public:

		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);
		void OnImGuiRender();

	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionEntity;
	};

}