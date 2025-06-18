#pragma once

#ifdef  PF_PLATFORM_WINDOWS
	#ifdef PF_BUILD_DLL
		#define PF_API __declspec(dllexport)
	#else
		#define PF_API __declspec(dllimport)
	#endif
#else 
	#error Pixel Forge Only supports windows
#endif //  GE_PLATFORM_WINDOWS
