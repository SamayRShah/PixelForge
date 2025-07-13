#include "pfpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace PixelForge {
	VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: PF_CORE_ASSERT(false, "Renderer API::None is not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}
		PF_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}