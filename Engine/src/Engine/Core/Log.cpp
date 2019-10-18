#include "enginepch.h"


#include "Log.h"

namespace Engine 
{

	std::shared_ptr<spdlog::logger> Log::coreLogger;
	std::shared_ptr<spdlog::logger> Log::clientLogger;

	void Log::init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		
		coreLogger = spdlog::stdout_color_mt("ENGINE");
		coreLogger->set_level(spdlog::level::trace);

		clientLogger = spdlog::stdout_color_mt("CLIENT");
		coreLogger->set_level(spdlog::level::trace);
	}

}
