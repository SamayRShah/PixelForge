#include "pfpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace PixelForge {
	Ref<Texture2D> Texture2D::Create(const std::string& path) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: PF_CORE_ASSERT(false, "Renderer API::None is not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}
		PF_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}
