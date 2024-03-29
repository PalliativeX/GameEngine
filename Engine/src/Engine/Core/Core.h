#pragma once

#include <memory>

#ifdef ENGINE_PLATFORM_WINDOWS
#ifdef ENGINE_DYNAMIC_LINK
	#ifdef ENGINE_BUILD_DLL
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif 
#else
	#define ENGINE_API
#endif
#else
	#error Engine only support Windows!
#endif 

#ifdef ENGINE_DEBUG
	#define ENGINE_ENABLE_ASSERTS
#endif

#ifdef ENGINE_ENABLE_ASSERTS
	#define ENGINE_ASSERT(x, ...) {if (!(x)){ENGINE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__);__debugbreak();}}
	#define CLIENT_ASSERT(x, ...) {if (!(x)){CLIENT_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__);__debugbreak();}}
#else
	#define ENGINE_ASSERT(x, ...)
	#define CLIENT_ASEERT(x, ...)
#endif 


#define BIT(x) (1 << x)

#define BIND_EVENT(function) std::bind(&function, this, std::placeholders::_1)

namespace Engine
{

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) 
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}