#pragma once  
#include "Core.h"  
#pragma warning(push, 0)  
#include <spdlog/spdlog.h>  
#include <spdlog/fmt/ostr.h>  
#pragma warning(pop)  

namespace PixelForge {  
	class  Log  
	{  
	public:  
		static void Init();  
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }  
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }  
	private:  
		// Remove  from static members to fix E1393  
		static std::shared_ptr<spdlog::logger> s_CoreLogger;  
		static std::shared_ptr<spdlog::logger> s_ClientLogger;  
	};  
}  

#define PF_CORE_TRACE(...)		::PixelForge::Log::GetCoreLogger()->trace(__VA_ARGS__)  
#define PF_CORE_INFO(...)		::PixelForge::Log::GetCoreLogger()->info(__VA_ARGS__)  
#define PF_CORE_ERROR(...)		::PixelForge::Log::GetCoreLogger()->error(__VA_ARGS__)  
#define PF_CORE_WARN(...)		::PixelForge::Log::GetCoreLogger()->warn(__VA_ARGS__)  
#define PF_CORE_CRITICAL(...)	::PixelForge::Log::GetCoreLogger()->critical(__VA_ARGS__)  

#define PF_TRACE(...)			::PixelForge::Log::GetClientLogger()->trace(__VA_ARGS__)  
#define PF_INFO(...)			::PixelForge::Log::GetClientLogger()->info(__VA_ARGS__)  
#define PF_ERROR(...)			::PixelForge::Log::GetClientLogger()->error(__VA_ARGS__)  
#define PF_WARN(...)			::PixelForge::Log::GetClientLogger()->warn(__VA_ARGS__)  
#define PF_CRITICAL(...)		::PixelForge::Log::GetClientLogger()->critical(__VA_ARGS__)