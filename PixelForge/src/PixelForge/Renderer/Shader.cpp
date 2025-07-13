#include "pfpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace PixelForge {
	Ref<Shader> Shader::Create(const std::string& path) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: PF_CORE_ASSERT(false, "Renderer API::None is not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(path);
		}
		PF_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: PF_CORE_ASSERT(false, "Renderer API::None is not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}
		PF_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader) {
		PF_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader) {
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath) {
		Ref<Shader> shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath) {
		Ref<Shader> shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name) {
		PF_CORE_ASSERT(Exists(name), "Shader doesn't exist!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) {
		return m_Shaders.find(name) != m_Shaders.end();
	}
}