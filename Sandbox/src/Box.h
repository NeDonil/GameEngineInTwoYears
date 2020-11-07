#pragma once

#include <box2d/box2d.h>
#include <glm/glm.hpp>

#include <Engine.h>

namespace Sandbox
{

	class Box
	{
	public:

		Box() = default;
		Box(b2World* world, const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, bool dynamic = true);
		Box(b2World* world, const glm::vec2& position, const glm::vec2& size, const Engine::Ref<Engine::Texture2D>& texture, bool dynamic = true);

		void SetTexture(const Engine::Ref<Engine::Texture2D>& texture) { m_Texture = texture; }
		void SetColor(const glm::vec4& color) { m_Color = color; };

		const Engine::Ref<Engine::Texture2D>& GetTexture() { return m_Texture; }
		const glm::vec2& GetPosition() { return { m_Body->GetPosition().x, m_Body->GetPosition().y }; }
		const glm::vec2& GetSize() {return m_Size; }
		const glm::vec4& GetColor() { return m_Color; }
		const float GetAngle() { return m_Body->GetAngle(); }

		~Box() = default;
	private:
		void Init(b2World* world, const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, bool dynamic);
	private:
		glm::vec2 m_Size;
		glm::vec4 m_Color;

		Engine::Ref<Engine::Texture2D> m_Texture;

		b2Body* m_Body = nullptr;
		b2Fixture* m_Fixture = nullptr;
	};

}