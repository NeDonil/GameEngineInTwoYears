#include <enpch.h>
#include "LayerStack.h"

namespace Engine
{
	LayerStack::LayerStack()
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
	}

	LayerStack::~LayerStack()
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
			m_Layers.erase(it);
	}
}