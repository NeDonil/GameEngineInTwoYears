#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS
	#ifdef ENGINE_BUILD_DLL
		#define ENGINE_API __declspec(dllexport)
	#else 
		#define ENGINE_API __declspec(dllimport)
	#endif
#else
	#error This Engine support only Windows
#endif

#define ENGINE_CORE_WARN(...)       Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ENGINE_CORE_CRITICAL(...)   Engine::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define ENGINE_CORE_INFO(...)       Engine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ENGINE_CORE_TRACE(...)      Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ENGINE_CORE_ERROR(...)      Engine::Log::GetCoreLogger()->error(__VA_ARGS__)

#define ENGINE_CLIENT_WARN(...)     Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ENGINE_CLIENT_CRITICAL(...) Engine::Log::GetClientLogger()->critical(__VA_ARGS__)
#define ENGINE_CLIENT_INFO(...)     Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define ENGINE_CLIENT_TRACE(...)    Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ENGINE_CLIENT_ERROR(...)    Engine::Log::GetClientLogger()->error(__VA_ARGS__)