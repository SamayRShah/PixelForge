#include <PixelForge.h>

class Sandbox : public PixelForge::Application {
public:
	Sandbox() {}
	~Sandbox() {}
};

PixelForge::Application* PixelForge::CreateApplication() {
	return new Sandbox();
}