#include <enpch.h>
#include "OrthographicCameraController.h"
#include "Engine/Core/Input.h"
#include <Engine/Core/KeyCodes.h>

namespace Engine
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation):
		m_AspectRatio(aspectRatio), m_Camera(-aspectRatio * m_ZoomLevel, aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}
	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(Engine::Key::W))
			m_CameraPosition.y += m_CameraTranslationSpeed * (float)ts;
		else if (Input::IsKeyPressed(Engine::Key::S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * (float)ts;
		if (Input::IsKeyPressed(Engine::Key::A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * (float)ts;
		else if (Input::IsKeyPressed(Engine::Key::D))
			m_CameraPosition.x += m_CameraTranslationSpeed * (float)ts;

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(Engine::Key::Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			else if (Input::IsKeyPressed(Engine::Key::E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	bool OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(ENGINE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(ENGINE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));

		return false;
	}

	void OrthographicCameraController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
		m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
	}

	void OrthographicCameraController::SetZoomLevel(float zoomLevel)
	{
		m_ZoomLevel = zoomLevel;

		m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
		m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
	}

	void OrthographicCameraController::SetPosition(const glm::vec3& position)
	{
		m_CameraPosition = position;

		m_Camera.SetPosition(m_CameraPosition);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
		m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
		return false;
	}
	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}
}