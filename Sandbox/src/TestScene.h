#pragma once

#include <Engine.h>

using namespace Engine;

class TestSceneLayer : public Layer
{
public:
	TestSceneLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Event& e) override;


	~TestSceneLayer() = default;
private:
	bool OnWindowResized(WindowResizeEvent& e);
private:
	Ref<Scene> m_MainScene;
};
