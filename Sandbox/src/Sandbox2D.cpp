#include <chrono>
#include "Sandbox2D.h"
#include "Engine/Core/EntryPoint.h"

template <typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& func) :
		m_Name(name), m_Func(func), m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;

		float duration = (end - start) * 0.001f;
		m_Func({ m_Name, duration });
	}
private:
	const char* m_Name;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
	Fn m_Func;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })

Sandbox2D::Sandbox2D():
	Layer("Layer2D"), m_CameraController((float)1280 / 720, true)
{

}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Engine::Texture2D::Create("assets/textures/Checkerboard.png");
	m_Texture = Engine::Texture2D::Create("assets/textures/icon.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Engine::Timestep ts)
{
	PROFILE_SCOPE("Sandbox2D::OnUpdate");
	m_CameraController.OnUpdate(ts);

	{
		PROFILE_SCOPE("Sandbox2D::Renderer prep");
		Engine::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		Engine::RenderCommand::Clear();
	}

	{
		PROFILE_SCOPE("Sandbox2D::Renderer draw");
		Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Engine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8, 0.8 }, { 0.2, 0.3, 0.8f, 1.0f });
		Engine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5, 0.75 }, m_SquareColor);

		Engine::Renderer2D::DrawQuad({ 1.5f,  -1.0f }, { 5.0, 0.25 }, m_RedColor);
		Engine::Renderer2D::DrawQuad({ 1.5f,  -1.25f }, { 5.0, 0.25 }, m_OrangeColor);
		Engine::Renderer2D::DrawQuad({ 1.5f,  -1.50f }, { 5.0, 0.25 }, m_YellowColor);
		Engine::Renderer2D::DrawQuad({ 1.5f,  -1.75f }, { 5.0, 0.25 }, m_GreenColor);
		Engine::Renderer2D::DrawQuad({ 1.5f,  -2.0f }, { 5.0, 0.25 }, m_BlueColor);
		Engine::Renderer2D::DrawQuad({ 1.5f,  -2.25f }, { 5.0, 0.25 }, m_PurpleColor);

		Engine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
		Engine::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Square");

	ImGui::ColorEdit4("Square color", glm::value_ptr(m_SquareColor));
	ImGui::ColorEdit4("Red color", glm::value_ptr(m_RedColor));
	ImGui::ColorEdit4("Orange color", glm::value_ptr(m_OrangeColor));
	ImGui::ColorEdit4("Yellow color", glm::value_ptr(m_YellowColor));
	ImGui::ColorEdit4("Green color", glm::value_ptr(m_GreenColor));
	ImGui::ColorEdit4("Blue color", glm::value_ptr(m_BlueColor));
	ImGui::ColorEdit4("Square Purple", glm::value_ptr(m_PurpleColor));

	for (auto& result : m_ProfileResults)
	{
		char label[50];
		strcpy(label, "  %.3fms");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();

	ImGui::End();
}

void Sandbox2D::OnEvent(Engine::Event& e)
{
	m_CameraController.OnEvent(e);
}
