#include "pfpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace PixelForge {
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			PF_CORE_ASSERT(false, "RenderAPI::NONE is not supported");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}
		PF_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}
}