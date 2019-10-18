#pragma once

#include "enginepch.h"

#include "Core.h"
#include "Engine/Events/Event.h"

namespace Engine 
{

	struct WindowProps
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps(const std::string &Title = "Engine", 
					unsigned int Width = 1280, 
					unsigned int Height = 720)
					: title(Title), width(Width), height(Height)
		{
		}

	};

	class ENGINE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window()
		{
		}

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		virtual void setEventCallback(const EventCallbackFn &callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSyncEnabled() const = 0;

		virtual void* getNativeWindow() const = 0;

		static Window *create(const WindowProps &props = WindowProps());
	};

}