#pragma once

#ifdef PF_PLATFORM_WINDOWS

extern PixelForge::Application* PixelForge::CreateApplication();

int main(int argc, char** argv) {
	printf("Starting engine");
	auto app = PixelForge::CreateApplication();
	app->Run();
	delete app;
}

#endif