#include "enpch.h"
#include "Animation2D.h"

namespace Engine
{

	Animation2D::Animation2D(const Ref<Texture2D>& texture,const glm::vec2& beginAnimation, const glm::vec2& frameSize, uint32_t frames, float speed)
		: m_Speed(speed), m_TimeRemaining(speed)
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		for (uint32_t i = 0; i < frames; i++)
		{
			SubTexture2D subtexture = *SubTexture2D::GetFromCoords(texture, { beginAnimation.x + i, beginAnimation.y }, frameSize);
			m_Frames.push_back(subtexture);
		}
	}

	Ref<Animation2D> Animation2D::Create(const Ref<Texture2D>& texture, const glm::vec2& beginAnimation, const glm::vec2& frameSize, uint32_t frames, float speed)
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		return CreateRef<Animation2D>(Animation2D(texture, beginAnimation, frameSize, frames, speed));
	}

	void Animation2D::OnUpdate(Timestep ts)
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		if (m_Playing)
		{
			m_TimeRemaining -= (float)ts;
			if (m_TimeRemaining <= 0)
			{
				m_CurrentFrame = (m_CurrentFrame + 1) % 5;
				m_TimeRemaining = m_Speed;
			}
		}
	}

	void Animation2D::Draw(OrthographicCamera& camera)
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		Engine::Renderer2D::BeginScene(camera);
		Engine::Renderer2D::DrawQuad(m_Position, m_Size, CreateRef<SubTexture2D>(m_Frames[m_CurrentFrame]));
		Engine::Renderer2D::EndScene();
	}

}
