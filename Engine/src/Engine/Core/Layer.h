#pragma once

#include "Core.h"
#include "Engine/Events/Event.h"

#include "Timestep.h"

namespace Engine 
{

	class ENGINE_API Layer
	{
	public:
		Layer(const std::string &Name = "Layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate(Timestep ts) {}
		virtual void onEvent(Event &event) {}

		virtual void onImGuiRender() {}

		inline const std::string getName() const { return debugName; }

	protected:
		std::string debugName;
	};

}