#include "pfpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace PixelForge {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				PF_CORE_ASSERT(false, "RenderAPI::NONE is not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return new OpenGLVertexBuffer(vertices, size);
		}
		PF_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				PF_CORE_ASSERT(false, "RenderAPI::NONE is not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return new OpenGLIndexBuffer(indices, count);
		}
		PF_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}

}