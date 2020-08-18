#include <enpch.h>
#include "Layer.h"

namespace Engine
{
	Layer::Layer(const std::string& debugName) :
		m_DebugName(debugName)
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
	}

	Layer::~Layer()
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
	}
}