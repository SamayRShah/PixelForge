#pragma once
#include "Event.h"

namespace PixelForge {
	class  E_MouseMove : public Event {
	public:
		E_MouseMove(float x, float y)
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

	class  E_MouseScroll : public Event {
	public:
		E_MouseScroll(float x, float y)
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

	class  E_MB : public Event {
	public:
		inline int GetMouseButton() const { return m_Button; }
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryMouseButton)
	protected:
		E_MB(int button)
			: m_Button(button){}
		int m_Button;
	};

	class  E_MBDown : public E_MB {
	public:
		E_MBDown(int button)
			:E_MB(button){}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MB_Down)
	};

	class  E_MBUp : public E_MB {
	public:
		E_MBUp(int button)
			:E_MB(button) {
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MB_Up)
	};
}