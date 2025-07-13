#pragma once
#include "PixelForge/Core/Core.h"
#include "PixelForge/Core/Timestep.h"
#include "PixelForge/Events/Event.h"

namespace PixelForge {
	class  Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttatch() {}
		virtual void OnDetatch() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}