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

#define BIT(x) (x << 1)

#ifdef ENGINE_ENABLE_ASSERTS
	#define ENGINE_CORE_ASSERT(x, ...) { (if(!x)){ENGINE_CORE_ERROR("Assertion Failed : {0}", __VA__ARGS__); __debugbreak;} } 
	#define ENGINE_CLIENT_ASSERT(x, ...) { (if(!x)){ENGINE_CLIENT_ERROR("Assertion Failed : {0}", __VA__ARGS__); __debugbreak;} } 
#else
	#define ENGINE_CORE_ASSERT(x, ...)
	#define ENGINE_CLIENT_ASSERT(x, ...)
#endif
