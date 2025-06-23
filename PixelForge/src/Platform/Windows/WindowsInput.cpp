#include "pfpch.h"
#include "WindowsInput.h"

#include "PixelForge/Application.h"
#include <GLFW/glfw3.h>

namespace PixelForge {
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyDownImpl(int keyCode) {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keyCode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool WindowsInput::IsMBDownImpl(int button) {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}
	std::pair<float, float> WindowsInput::GetMousePosImpl() {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}
	float WindowsInput::GetMouseXImpl() {
		auto [x, _] = GetMousePosImpl();
		return x;
	}
	float WindowsInput::GetMouseYImpl() {
		auto [_, y] = GetMousePosImpl();
		return y;
	}
 }

