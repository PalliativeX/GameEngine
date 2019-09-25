#pragma once

#include "Event.h"

namespace Engine 
{

	class ENGINE_API KeyEvent : public Event
	{
	public:
		inline int getKeyCode() const
		{
			return keycode;
		}

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int Keycode) : keycode(Keycode)
		{
		}

		int keycode;
	};

	class ENGINE_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int Keycode, int RepeatCount) : KeyEvent(Keycode), repeatCount(RepeatCount) {}

		inline int getRepeatCount() const
		{
			return repeatCount;
		}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << keycode << " (" << repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int repeatCount;
	};

	class ENGINE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int Keycode) : KeyEvent(Keycode)
		{
		}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class ENGINE_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int Keycode) : KeyEvent(Keycode)
		{
		}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

}