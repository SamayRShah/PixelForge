#pragma once

#ifdef PF_PLATFORM_WINDOWS

extern PixelForge::Application* PixelForge::CreateApplication();

int main(int argc, char** argv) {
	PixelForge::Log::Init();
	PF_CORE_WARN("Initialized log!");
	PF_INFO("Hello!");

	auto app = PixelForge::CreateApplication();
	app->Run();
	delete app;
}

#endif