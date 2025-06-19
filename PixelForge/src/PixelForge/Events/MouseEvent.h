#pragma once
#include "Event.h"
#include <sstream>

namespace PixelForge {
	class PF_API MouseMoveEvent : public Event {
	public:
		MouseMoveEvent(float x, float y)
			:m_MouseX(x), m_MouseY(y){}

		inline float GetX() const { return  m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMoveEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse)
		EVENT_CLASS_TYPE(MouseMove)

	private:
		float m_MouseX, m_MouseY;
	};

	class PF_API MouseScrollEvent : public Event {
	public:
		MouseScrollEvent(float x, float y)
			:m_XOffset(x), m_YOffset(y) {
		}

		inline float GetX() const { return  m_XOffset; }
		inline float GetY() const { return m_YOffset; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrollEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScroll)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_XOffset, m_YOffset;
	};

	class PF_API MouseButtonEvent : public Event {
	public:
		inline int GetMouseButton() const { return m_Button; }
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryMouseButton)
	protected:
		MouseButtonEvent(int button)
			: m_Button(button){}
		int m_Button;
	};

	class PF_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button)
			:MouseButtonEvent(button){}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class PF_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button)
			:MouseButtonEvent(button) {
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}