#pragma once

#ifdef CTN_PLATFORM_WINDOWS
	#ifdef CTN_BUILD_DLL
		#define CENTURION_API __declspec(dllexport)
	#else
		#define CENTURION_API __declspec(dllimport)
	#endif // !CTN_BUILD_DLL
#else
	#error Centurion only support Windows!
#endif // !CTN_PLATFORM_WINDOWS

#ifdef CTN_ENABLE_ASSERTS
	#define CTN_ASSERT(x, ...) { if(!(x)) { CTN_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define CTN_CORE_ASSERT(x, ...) { if(!(x)) { CTN_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define CTN_ASSERT(x, ...)
	#define CTN_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define CTN_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1) 