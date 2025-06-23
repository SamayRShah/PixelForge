#pragma once
#include "PixelForge/Core.h"
#include "PixelForge/Events/Event.h"

namespace PixelForge {
	class  Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttatch() {}
		virtual void OnDetatch() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}