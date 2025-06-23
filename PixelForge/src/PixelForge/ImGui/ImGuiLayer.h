#pragma once
#include "PixelForge/Layer.h"
#include "PixelForge/Events/Event.h"
#include "PixelForge/Events/ApplicationEvent.h"
#include "PixelForge/Events/MouseEvent.h"
#include "PixelForge/Events/KeyEvent.h"


namespace PixelForge {
	class  ImGuiLayer: public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttatch() override;
		virtual void OnDetatch() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}


