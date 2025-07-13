#pragma once
#include "Event.h"

namespace PixelForge {
	class  MouseMoveEvent : public Event {
	public:
		MouseMoveEvent(float x, float y)
			:m_MouseX(x), m_MouseY(y){}

		inline float GetXOffset() const { return  m_MouseX; }
		inline float GetYOffset() const { return m_MouseY; }

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

	class  MouseScrollEvent : public Event {
	public:
		MouseScrollEvent(float x, float y)
			:m_XOffset(x), m_YOffset(y) {
		}

		inline float GetXOffset() const { return  m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

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

	class  MouseButtonEvent : public Event {
	public:
		inline int GetMouseButton() const { return m_Button; }
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryMouseButton)
	protected:
		MouseButtonEvent(int button)
			: m_Button(button){}
		int m_Button;
	};

	class  MouseButtonDownEvent : public MouseButtonEvent {
	public:
		MouseButtonDownEvent(int button)
			:MouseButtonEvent(button){}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonDown)
	};

	class  MouseButtonUpEvent : public MouseButtonEvent {
	public:
		MouseButtonUpEvent(int button)
			:MouseButtonEvent(button) {
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonUp)
	};
}