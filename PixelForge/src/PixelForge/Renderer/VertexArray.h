#pragma once  

#include "PixelForge/Renderer/Buffer.h"  
#include <memory>  
#include <vector>  

namespace PixelForge {  

	class VertexArray {  
	public:  
		virtual ~VertexArray() = default;  

		virtual void Bind() const = 0;  
		virtual void Unbind() const = 0;  

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;  
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;  

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;  
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;  

		static VertexArray* Create();  
	};  
}