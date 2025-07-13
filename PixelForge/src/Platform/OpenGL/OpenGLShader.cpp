#include "pfpch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace PixelForge {

	static GLenum ShaderTypeFromString(const std::string& type) {
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;
		
		PF_CORE_ASSERT(false, "Unknown Shader type");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath) {
		std::string source = ReadFile(filepath);
		std::unordered_map<GLenum, std::string> shaderSources = PreProcess(source);
		Compile(shaderSources);

		// extracting name:
		// assets/shaders/texture.glsl -> texture
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_Name(name)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSrc;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(shaderSources);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath) {
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in) {
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else {
			PF_CORE_ERROR("Could not open file: {0}", filepath);
		}
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source) {
		std::unordered_map<GLenum, std::string> shaderSources;

		// find type in file, and move 'cursor' to position
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos) {
			// find next end of line after the token
			size_t eol = source.find_first_of("\r\n", pos);
			PF_CORE_ASSERT(eol != std::string::npos, "Syntax Error");

			// read type from 1 space ahead
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			PF_CORE_ASSERT(ShaderTypeFromString(type), "Invalid Shader type specified");

			// find next type token from the next line
			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);

			// assign string from next line to the end of file, or next line pos if there is another type token
			// as shader source
			shaderSources[ShaderTypeFromString(type)] =
				source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources) {

		// Create a program object.
		GLuint program = glCreateProgram();
		PF_CORE_ASSERT(shaderSources.size() <= 2, "We only support 2 shaders for now");
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;
		for (auto& [type, src] : shaderSources) {

			// create shader handle
			GLuint shader = glCreateShader(type);

			const GLchar* source = src.c_str();
			glShaderSource(shader, 1, &source, 0);

			// Compile the vertex shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				PF_CORE_ERROR("{0}", infoLog.data());
				PF_CORE_ASSERT(false, "Shader Compilation failure!");
				break;
			}
			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		// Link our program
		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);

		// clean up for failed link
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			
			for (auto id : glShaderIDs)
				glDeleteShader(id);

			PF_CORE_ERROR("{0}", infoLog.data());
			PF_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// Always detach shaders after a successful link.
		for (auto id : glShaderIDs)
			glDetachShader(program, id);

		// set program to renderID on successful compilation
		m_RendererID = program;
	}

	void OpenGLShader::Bind() const {
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const {
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int val) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, val);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float val) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, val);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& vals) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, vals.x, vals.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& vals) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, vals.x, vals.y, vals.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& vals) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, vals.x, vals.y, vals.z, vals.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}