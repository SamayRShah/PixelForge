workspace "PixelForge"
	architecture "x64"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "PixelForge"
	location "PixelForge"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/".. outputdir .. "/%{prj.name}")
	objdir ("bin-int/".. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"PixelForge/vendor/spdlog/include",
		"%{prj.name}/src"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		buildoptions { "/utf-8" }

		defines{
			"PF_PLATFORM_WINDOWS",
			"PF_BUILD_DLL"
		}

		postbuildcommands{
			"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"
		}

	filter "configurations:Debug"
		defines "PF_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "PF_Release"
		optimize "On"

	filter "configurations:Dist"
		defines "PF_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/".. outputdir .. "/%{prj.name}")
	objdir ("bin-int/".. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"PixelForge/vendor/spdlog/include",
		"PixelForge/src"
	}

	links {
		"PixelForge"
	}

	filter "system:windows"
		cppdialect "Default"
		staticruntime "On"
		systemversion "latest"

		buildoptions { "/utf-8" }

		defines{
			"PF_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "PF_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "PF_Release"
		optimize "On"

	filter "configurations:Dist"
		defines "PF_DIST"
		optimize "On"