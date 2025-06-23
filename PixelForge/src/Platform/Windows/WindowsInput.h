#pragma once
#include "PixelForge/Input.h"

namespace PixelForge {
	class WindowsInput : public Input {
	protected:
		virtual bool IsKeyDownImpl(int keyCode) override;
		virtual bool IsMBDownImpl(int button) override;
		virtual std::pair<float, float> GetMousePosImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}