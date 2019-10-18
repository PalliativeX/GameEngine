#pragma once

#include "Engine/Core/Input.h"

namespace Engine 
{

	class WindowsInput : public Input
	{
		virtual bool isKeyPressedImpl(int keycode) override;

		virtual bool isMousePressedImpl(int button) override;
		virtual std::pair<float, float> getMousePositionImpl() override;
		virtual float getMouseXImpl() override;
		virtual float getMouseYImpl() override;
	};

}