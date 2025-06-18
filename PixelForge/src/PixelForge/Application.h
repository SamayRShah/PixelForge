#pragma once
#include "Core.h"
namespace PixelForge{
	class PF_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}