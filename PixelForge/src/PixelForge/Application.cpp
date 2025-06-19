#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace PixelForge {
	Application::Application() {}
	Application::~Application() {}

	void Application::Run() {
		WindowResizeEvent e(1280, 720);
		PF_CORE_TRACE(e);

		while (true) {}
	}
}