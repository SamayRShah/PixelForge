#pragma once
#include "pfpch.h"
#include "Event.h"

namespace PixelForge {
	class  E_WindowResize : public Event {
	public:
		E_WindowResize(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height){}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Window Resize Event: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_Width, m_Height;
	};


	class  E_WindowClose : public Event {
	public:
		E_WindowClose() {}
		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class  E_AppTick : public Event {
	public:
		E_AppTick() {}
		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class  E_AppUpdate : public Event {
	public:
		E_AppUpdate() {}
		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class  E_AppRender : public Event {
	public:
		E_AppRender() {}
		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

}