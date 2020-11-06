#pragma once

#include <box2d/box2d.h>
#include <glm/glm.hpp>

namespace Sandbox
{

	class Box
	{
	public:

		Box() = default;
		Box(b2World* world, const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);

		~Box() = default;
	public:
		glm::vec2 m_Position;
		glm::vec2 m_Size;
		glm::vec4 m_Color;

		b2Body* m_Body = nullptr;
		b2Fixture* m_Fixture = nullptr;
	};

}