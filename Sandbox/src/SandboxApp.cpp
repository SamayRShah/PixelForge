#include "PixelForge.h"
#include "imgui/repo/imgui.h"
#include <glm/gtc/matrix_transform.hpp>

// temporary
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>


class ExLayer : public PixelForge::Layer {
public:
	ExLayer()
		:Layer("Example"), m_CameraController(1280.0f/720.0f, true) {

		m_VertexArray.reset(PixelForge::VertexArray::Create());

		float vertices[3 * 3 + 4 * 3] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.2f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
		};

		PixelForge::Ref<PixelForge::VertexBuffer> triVB;
		triVB.reset(PixelForge::VertexBuffer::Create(vertices, sizeof(vertices)));

		triVB->SetLayout({
			{ PixelForge::ShaderDataType::Float3, "a_Position"},
			{ PixelForge::ShaderDataType::Float4, "a_Color" }
			});
		m_VertexArray->AddVertexBuffer(triVB);

		uint32_t indices[3] = { 0, 1, 2 };
		PixelForge::Ref<PixelForge::IndexBuffer> triIB;
		triIB.reset(PixelForge::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(triIB);

		float squareVertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		m_SquareVA.reset(PixelForge::VertexArray::Create());
		PixelForge::Ref<PixelForge::VertexBuffer> squareVB;

		squareVB.reset(PixelForge::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
				{ PixelForge::ShaderDataType::Float3, "a_Position" },
				{ PixelForge::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndeces[6] = { 0, 1, 2, 2, 3, 0 };
		PixelForge::Ref<PixelForge::IndexBuffer> squareIB;
		squareIB.reset(PixelForge::IndexBuffer::Create(squareIndeces, sizeof(squareIndeces) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main(){
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";
		std::string fragSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4  color;
			in vec3 v_Position;
			in vec4 v_Color;

			void main(){
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";
		m_Shader = PixelForge::Shader::Create("TriangleShader", vertexSrc, fragSrc);

		std::string flatColorVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main(){
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";
		std::string FlatColorFragSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4  color;
			in vec3 v_Position;

			uniform vec3 u_Color;

			void main(){
				color = vec4(u_Color, 1.0);
			}
		)";
		m_FlatColorShader = PixelForge::Shader::Create("m_FlatColorShader", flatColorVertexSrc, FlatColorFragSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		
		m_Texture = PixelForge::Texture2D::Create("assets/textures/checkerboard.png");
		m_TextureThwacked = PixelForge::Texture2D::Create("assets/textures/thwacked.png");

		std::dynamic_pointer_cast<PixelForge::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<PixelForge::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	virtual void OnUpdate(PixelForge::Timestep ts) override {

		// update	
		m_CameraController.OnUpdate(ts);

		// frame rate debug
		{
			m_FrameRate = 1.0f / ts;

			// Track frame times (or frame rates)
			m_FrameTimes.push_back(m_FrameRate);
			if (m_FrameTimes.size() > m_FrameSampleCount)
				m_FrameTimes.erase(m_FrameTimes.begin()); // Keep size constant

			// Compute average
			float total = 0.0f;
			for (float rate : m_FrameTimes)
				total += rate;
			m_AvgFrameRate = total / m_FrameTimes.size();

			// PF_TRACE("Delta time: {0}s", ts.GetSeconds());
		}

		PixelForge::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		PixelForge::RenderCommand::Clear();

		PixelForge::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<PixelForge::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<PixelForge::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 15; y++) {
			for (int x = 0; x < 15; x++) {
				glm::vec3 pos(x * 0.11f - 0.75f, y * 0.11f - 0.75f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				PixelForge::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		PixelForge::Renderer::Submit(textureShader, m_SquareVA);
		m_TextureThwacked->Bind();
		PixelForge::Renderer::Submit(textureShader, m_SquareVA);

		// Triangle
		// PixelForge::Renderer::Submit(m_Shader, m_VertexArray);

		PixelForge::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Inspector");
		if (ImGui::CollapsingHeader("App Details")) {
			ImGui::Text("Current frame rate: %.2f Hz", m_FrameRate);
			ImGui::Text("Average frame rate: %.2f Hz", m_AvgFrameRate);
		}
		if (ImGui::CollapsingHeader("Program")) {
			ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		}
		ImGui::End();
	}

	virtual void OnEvent(PixelForge::Event& e) override {
		m_CameraController.OnEvent(e);
	}

private:
	PixelForge::ShaderLibrary m_ShaderLibrary;
	PixelForge::Ref<PixelForge::Shader> m_Shader;
	PixelForge::Ref<PixelForge::Shader> m_FlatColorShader;

	PixelForge::Ref<PixelForge::VertexArray> m_VertexArray;
	PixelForge::Ref<PixelForge::VertexArray> m_SquareVA;

	PixelForge::Ref<PixelForge::Texture2D> m_Texture;
	PixelForge::Ref<PixelForge::Texture2D> m_TextureThwacked;
    
	PixelForge::OrthographicCameraController m_CameraController;
	glm::vec3 m_CamPos = { 0, 0, 0 };
private:
	glm::vec3 m_SquareColor = { 0.8f, 0.3f, 0.3f };
private:
	// frame rate debug
	std::vector<float> m_FrameTimes;
	float m_FrameRate = 0;
	float m_AvgFrameRate = 0.0f;
	const size_t m_FrameSampleCount = 100;
};

class Sandbox : public PixelForge::Application {
public:
	Sandbox() {
		PushLayer(new ExLayer());
	}
	~Sandbox() {}
};

PixelForge::Application* PixelForge::CreateApplication() {
	return new Sandbox();
}