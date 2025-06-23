project "ImGui"
    kind "staticLib"
    language "C++"
    staticruntime "on"
    cppdialect "C++latest"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "repo/imconfig.h",
        "repo/imgui.cpp",
        "repo/imgui.h",
        "repo/imgui_demo.cpp",
        "repo/imgui_draw.cpp",
        "repo/imgui_internal.h",
        "repo/imgui_tables.cpp",
        "repo/imgui_widgets.cpp",
        "repo/imstb_rectpack.h",
        "repo/imstb_textedit.h",
        "repo/imstb_truetype.h"
    }

    filter "system:windows"
        systemversion "latest"
	
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"