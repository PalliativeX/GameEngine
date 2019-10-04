#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Engine 
{

	class ENGINE_API Log
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return clientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
	};

}

#define ENGINE_LOG_ERROR(...) ::Engine::Log::getCoreLogger()->error(__VA_ARGS__)
#define ENGINE_LOG_WARN(...)  ::Engine::Log::getCoreLogger()->warn(__VA_ARGS__)
#define ENGINE_LOG_INFO(...)  ::Engine::Log::getCoreLogger()->info(__VA_ARGS__)
#define ENGINE_LOG_TRACE(...) ::Engine::Log::getCoreLogger()->trace(__VA_ARGS__)
#define ENGINE_LOG_FATAL(...) ::Engine::Log::getCoreLogger()->fatal(__VA_ARGS__)

#define CLIENT_LOG_ERROR(...) ::Engine::Log::getClientLogger()->error(__VA_ARGS__)
#define CLIENT_LOG_WARN(...)  ::Engine::Log::getClientLogger()->warn(__VA_ARGS__)
#define CLIENT_LOG_INFO(...)  ::Engine::Log::getClientLogger()->info(__VA_ARGS__)
#define CLIENT_LOG_TRACE(...) ::Engine::Log::getClientLogger()->trace(__VA_ARGS__)
#define CLIENT_LOG_FATAL(...) ::Engine::Log::getClientLogger()->fatal(__VA_ARGS__)

