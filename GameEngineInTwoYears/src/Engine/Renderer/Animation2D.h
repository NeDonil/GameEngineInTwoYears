#pragma once

#include "Engine.h"
#include "Texture.h"
#include "SubTexture2D.h"

#include "glm/glm.hpp"

#include <vector>

namespace Engine
{
	class Animation2D
	{
	public:
		Animation2D(const Ref<Texture2D>& texture, const glm::vec2& beginAnimation, const glm::vec2& frameSize, uint32_t frames, float speed = 1.0f);

		static Ref<Animation2D> Create(const Ref<Texture2D>& texture, const glm::vec2& beginAnimation, const glm::vec2& frameSize, uint32_t frames, float speed = 1.0f);

		const float& GetSpeed() const { return m_Speed; }
		void SetSpeed(const float& speed) { m_Speed = speed; m_TimeRemaining = speed; }

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; }

		const glm::vec2& GetSize() const { return m_Size; }
		void SetSize(const glm::vec2& size) { m_Size = size; }

		void OnUpdate(Timestep ts);
		void Draw(OrthographicCamera& camera);

		void Play(bool isPlayed) { m_Playing = isPlayed; }
	private:
		bool m_Playing;
		float m_TimeRemaining;
		float m_Speed;
		glm::vec3 m_Position;
		glm::vec2 m_Size;
		uint16_t m_CurrentFrame = 0;
		std::vector<SubTexture2D> m_Frames;
	};
}