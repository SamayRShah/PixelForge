#pragma once
#include "Core.h"
#include "Log.h"
#include "Window.h"
#include "PixelForge/Core/LayerStack.h"
#include "PixelForge/Events/Event.h"
#include "PixelForge/Events/ApplicationEvent.h"
#include "PixelForge/ImGui/ImGuiLayer.h"
#include "PixelForge/Core/Timestep.h"

namespace PixelForge{
	class  Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}