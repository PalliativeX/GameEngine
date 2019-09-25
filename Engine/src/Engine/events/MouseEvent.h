#pragma once

#include "Event.h"

namespace Engine 
{

	class ENGINE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) : mouseX(x), mouseY(y) {}

		inline float getX() const { return mouseX; }
		inline float getY() const { return mouseY; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << getX() << ", " << getY();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)



	private:
		float mouseX;
		float mouseY;
	};

	class ENGINE_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xoffset, float yoffset) : xOffset(xoffset), yOffset(yoffset) {}

		inline float getXOffset() const { return xOffset; }
		inline float getYOffset() const { return yOffset; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MousedScrolledEvent: " << getXOffset() << ", " << getYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)	
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)


	private:
		float xOffset;
		float yOffset;
	};

	class ENGINE_API MouseButtonEvent : public Event
	{
	public:
		inline int getMouseButton() const { return button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseButtonEvent(int Button) : button(Button) {}

		int button;
	};

	class ENGINE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int Button)
			: MouseButtonEvent(Button) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class ENGINE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int Button)
			: MouseButtonEvent(Button) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}