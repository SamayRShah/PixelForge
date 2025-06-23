#pragma once
#include "Core.h"
#include "Log.h"
#include "Window.h"
#include "PixelForge/LayerStack.h"
#include "PixelForge/Events/Event.h"
#include "PixelForge/Events/ApplicationEvent.h"
#include "PixelForge/ImGui/ImGuiLayer.h"
#include "PixelForge/Renderer/Shader.h"
#include "PixelForge/Renderer/Buffer.h"

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
		bool OnWindowClose(E_WindowClose& e);
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}