#pragma once
#include "Event.h"

namespace PixelForge {
	class  E_Key : public Event {
	public:
		inline int GetKeyCode() const { return m_KeyCode;  }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		E_Key(int keyCode)
			: m_KeyCode(keyCode) {}
		int m_KeyCode;
	};

	class  E_KeyTyped : public E_Key {
	public:
		E_KeyTyped(int keycode)
			: E_Key(keycode){ }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Key Typed: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	protected:
		int m_RepeatCount;
	};

	class  E_KeyDown : public E_Key {
	public:
		E_KeyDown(int keycode, int repeatCount)
			: E_Key(keycode), m_RepeatCount(repeatCount) {}

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

	class  E_KeyUp : public E_Key {
	public:
		E_KeyUp(int keyCode)
			:E_Key(keyCode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Key Released: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyUp)
	};
}