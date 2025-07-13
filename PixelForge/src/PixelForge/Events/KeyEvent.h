#pragma once
#include "Event.h"

namespace PixelForge {
	class  KeyEvent : public Event {
	public:
		inline int GetKeyCode() const { return m_KeyCode;  }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keyCode)
			: m_KeyCode(keyCode) {}
		int m_KeyCode;
	};

	class  KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode), m_RepeatCount(0){ }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Key Typed: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	protected:
		int m_RepeatCount;
	};

	class  KeyDownEvent : public KeyEvent {
	public:
		KeyDownEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Key Pressed: " << m_KeyCode << "( " << m_RepeatCount << " repeats )";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyDown)
	protected:
		int m_RepeatCount;
	};

	class  KeyUpEvent : public KeyEvent {
	public:
		KeyUpEvent(int keyCode)
			:KeyEvent(keyCode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Key Released: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyUp)
	};
}