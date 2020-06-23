#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

class Log
{
public:
	static void Init();

	inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
	inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
private:
	static std::shared_ptr<spdlog::logger> s_CoreLogger;
	static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

#define ENGINE_LOG_TRACE(...)	Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ENGINE_LOG_INFO(...)	Log::GetCoreLogger()->info(__VA_ARGS__)
#define ENGINE_LOG_WARN(...)	Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ENGINE_LOG_ERROR(...)	Log::GetCoreLogger()->error(__VA_ARGS__)
#define ENGINE_LOG_FATAL(...)	Log::GetCoreLogger()->critical(__VA_ARGS__)

#define GAME_LOG_TRACE(...)	Log::GetClientLogger()->trace(__VA_ARGS__)
#define GAME_LOG_INFO(...)	Log::GetClientLogger()->info(__VA_ARGS__)
#define GAME_LOG_WARN(...)	Log::GetClientLogger()->warn(__VA_ARGS__)
#define GAME_LOG_ERROR(...)	Log::GetClientLogger()->error(__VA_ARGS__)
#define GAME_LOG_FATAL(...)	Log::GetClientLogger()->critical(__VA_ARGS__)