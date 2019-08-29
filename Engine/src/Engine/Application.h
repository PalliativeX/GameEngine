#pragma once

#include "Core.h"

namespace Engine {

	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};

	// to be defined in CLIENT
	Application* createApplication();

}
