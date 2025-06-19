#pragma once
#include "Event.h"
#include <sstream>
namespace PixelForge {
	class PF_API KeyEvent : public Event {
	public:
		inline int GetKeyCode() const { return m_KeyCode;  }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keyCode)
			: m_KeyCode(keyCode) {}
		int m_KeyCode;
	};

	class PF_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Key Pressed: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	protected:
		int m_RepeatCount;
	};

	class PF_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keyCode)
			:KeyEvent(keyCode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Key Released: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}