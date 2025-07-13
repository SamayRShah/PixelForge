#include "pfpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace PixelForge {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}