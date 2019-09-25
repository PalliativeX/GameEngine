#pragma once
#include "Engine/Core.h"
#include "Layer.h"

#include <vector>

namespace Engine 
{

	class ENGINE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void pushLayer(Layer *layer);
		void pushOverlay(Layer *overlay);
		void popLayer(Layer *layer);
		void popOverlay(Layer *overlay);

		std::vector<Layer*>::iterator begin()
		{
			return layers.begin();
		}
		std::vector<Layer*>::iterator end()
		{
			return layers.end();
		}
	private:
		std::vector<Layer*> layers;
		unsigned int layerInsertIndex = 0;
	};

}