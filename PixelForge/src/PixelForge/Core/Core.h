#pragma once
#include <memory>

#ifdef PF_DEBUG
	#define PF_ENABLE_ASSERTS
#endif

#if defined(_MSC_VER)
	#define __debugBreak() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
	#include <signal.h>
	#define __debugBreak() raise(SIGTRAP)
#else
	#define __debugBreak() ((void)0)
#endif

#ifdef PF_ENABLE_ASSERTS
	#define PF_ASSERT(x, ...) { if(!(x)) { PF_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugBreak(); }}
	#define PF_CORE_ASSERT(x, ...) { if(!(x)) { PF_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugBreak(); }}
#else
	#define PF_ASSERT(x, ...)
	#define PF_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define PF_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace PixelForge {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}