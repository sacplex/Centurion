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

#define BIT(x) (1 << x)