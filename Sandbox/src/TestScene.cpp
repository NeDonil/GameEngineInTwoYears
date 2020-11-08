#pragma once

#include "TestScene.h"

void TestSceneLayer::OnAttach()
{
	m_MainScene = CreateRef<Scene>();

	SceneSerializer serializer(m_MainScene);
	serializer.Deserialize("assets/scenes/Sandbox.scene");

	uint32_t width  = Application::Get().GetWindow().GetWidth();
	uint32_t height = Application::Get().GetWindow().GetHeight();

	m_MainScene->OnViewportResize(width, height);
}

void TestSceneLayer::OnDetach()
{
}

void TestSceneLayer::OnUpdate(Timestep ts)
{
	RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	RenderCommand::Clear();

	m_MainScene->OnUpdate(ts);
}

void TestSceneLayer::OnImGuiRender()
{
}

void TestSceneLayer::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(ENGINE_BIND_EVENT_FN(TestSceneLayer::OnWindowResized));
}

bool TestSceneLayer::OnWindowResized(WindowResizeEvent& e)
{
	m_MainScene->OnViewportResize(e.GetWidth(), e.GetHeight());
	return true;
}
