#pragma once

#ifdef PF_PLATFORM_WINDOWS

extern PixelForge::Application* PixelForge::CreateApplication();

int main(int argc, char** argv) {
	PixelForge::Log::Init();
	PF_CORE_INFO("Initialized log!");

	auto app = PixelForge::CreateApplication();
	app->Run();
	delete app;
}

#endif