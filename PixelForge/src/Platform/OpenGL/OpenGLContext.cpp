#include "pfpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace PixelForge {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle) {
		PF_CORE_ASSERT(windowHandle, "Window Handle Is null!");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PF_CORE_ASSERT(status, "Failed to initialize GLAD");

		PF_CORE_INFO("OpenGL Info:");
		PF_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		PF_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		PF_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}
}