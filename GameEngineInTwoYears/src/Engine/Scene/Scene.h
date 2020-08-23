#pragma once

#include "Engine/Core/Timestep.h"
#include "entt.hpp"

namespace Engine
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		entt::registry& Reg() { return m_Registry; }

		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;
	};
}