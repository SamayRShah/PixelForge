#pragma once
#include "RenderCommand.h"
#include "RendererAPI.h"
#include "Camera.h"
#include "Shader.h"

namespace PixelForge {
	class Renderer {
	public:
		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t heights);

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, 
			const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};
}