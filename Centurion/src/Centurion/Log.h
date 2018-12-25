#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Centurion {

	class CENTURION_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define CTN_CORE_TRACE(...) ::Centurion::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CTN_CORE_INFO(...) ::Centurion::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CTN_CORE_WARN(...) ::Centurion::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CTN_CORE_ERROR(...) ::Centurion::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CTN_CORE_FATAL(...) ::Centurion::Log::GetCoreLogger()->fatal(__VA_ARGS__)


#define CTN_CLIENT_TRACE(...) ::Centurion::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CTN_CLIENT_INFO(...) ::Centurion::Log::GetClientLogger()->info(__VA_ARGS__)
#define CTN_CLIENT_WARN(...) ::Centurion::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CTN_CLIENT_ERROR(...) ::Centurion::Log::GetClientLogger()->error(__VA_ARGS__)
#define CTN_CLIENT_FATAL(...) ::Centurion::Log::GetClientLogger()->fatal(__VA_ARGS__)