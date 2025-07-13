#pragma once
#include "PixelForge/Core/Core.h"

namespace PixelForge {

	class  Input {
	public:
		static bool IsKeyDown(int keyCode) { return s_Instance->IsKeyDownImpl(keyCode); }
		static bool IsMBDown(int button) { return s_Instance->IsMBDownImpl(button); }
		static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }
		static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
	protected:
		virtual bool IsKeyDownImpl(int keyCode) = 0;
		virtual bool IsMBDownImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Input* s_Instance;
	};
}