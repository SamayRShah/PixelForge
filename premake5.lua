workspace "PixelForge"
	architecture "x64"
    startproject "Sandbox"

	configurations{
		"Debug", "Release", "Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include dirs relative to root
IncludeDir = {}
IncludeDir["GLFW"] = "PixelForge/vendor/GLFW/repo/include"
IncludeDir["Glad"] = "PixelForge/vendor/Glad/repo/include"
IncludeDir["imgui"] = "PixelForge/vendor/imgui/repo"
IncludeDir["glm"] = "PixelForge/vendor/glm/repo"

group "Dependencies"
	include "PixelForge/vendor/GLFW"
	include "PixelForge/vendor/Glad"
	include "PixelForge/vendor/imgui"
group ""

project "PixelForge"
	location "PixelForge"
	kind "StaticLib"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"

	targetdir ("bin/".. outputdir .. "/%{prj.name}")
	objdir ("bin-int/".. outputdir .. "/%{prj.name}")

	pchheader "pfpch.h"
	pchsource "PixelForge/src/pfpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",

		-- glm includes
		"%{prj.name}/vendor/glm/repo/glm/**.hpp",
		"%{prj.name}/vendor/glm/repo/glm/**.inl",
	}

	includedirs {
		"%{prj.name}/src",
		"PixelForge/vendor/spdlog/repo/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
	}

	links {
		"GLFW", "Glad",
		"ImGui", "opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		buildoptions { "/utf-8" }

		defines{
			"PF_PLATFORM_WINDOWS",
			"PF_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "PF_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PF_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "PF_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"

	targetdir ("bin/".. outputdir .. "/%{prj.name}")
	objdir ("bin-int/".. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"PixelForge/vendor/spdlog/repo/include",
		"PixelForge/src",
		"PixelForge/vendor",
		"%{IncludeDir.glm}"
	}

	links {
		"PixelForge"
	}

	filter "system:windows"
		systemversion "latest"

		buildoptions { "/utf-8" }

		defines{ "PF_PLATFORM_WINDOWS" }

	filter "configurations:Debug"
		defines "PF_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PF_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "PF_DIST"
		runtime "Release"
		optimize "on"