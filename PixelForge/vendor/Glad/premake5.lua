project "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "on"
    warnings "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files{
        "repo/include/glad/glad.h",
        "repo/include/KHR/khrplatform.h",
		"repo/src/glad.c"
    }

	includedirs { "repo/include" }

    filter "system:windows"
        systemversion "latest"
		
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

