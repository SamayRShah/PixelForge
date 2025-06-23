#include <PixelForge.h>
#include "imgui/repo/imgui.h"

class ExLayer : public PixelForge::Layer {
public:
	ExLayer()
		:Layer("Example"){}

	virtual void OnUpdate() override {
		if (PixelForge::Input::IsKeyDown(PF_KEY_TAB))
			PF_INFO("Tab key pressed");
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Test");
		ImGui::Text("Hello world");
		ImGui::End();
	}
};

class Sandbox : public PixelForge::Application {
public:
	Sandbox() {
		PushLayer(new ExLayer());
	}
	~Sandbox() {}
};

PixelForge::Application* PixelForge::CreateApplication() {
	return new Sandbox();
}