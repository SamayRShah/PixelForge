#include "pfpch.h"
#include "LayerStack.h"

namespace PixelForge {
	LayerStack::LayerStack() { }

	LayerStack::~LayerStack() {
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer) {
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
		layer->OnAttatch();
	}

	void LayerStack::PushOverlay(Layer* overlay) {
		m_Layers.emplace_back(overlay);
		overlay->OnAttatch();
	}

	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it == m_Layers.end()) return;
		m_Layers.erase(it);
		m_LayerInsertIndex--;
		layer->OnDetatch();
	}

	void LayerStack::PopOverlay(Layer* overlay) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it == m_Layers.end()) return;
		m_Layers.erase(it);
		overlay->OnDetatch();
	}
}