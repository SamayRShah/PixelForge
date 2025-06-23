project "GLFW"
    kind "StaticLib"
    language "C"
    staticruntime "on"
    warnings "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files{
        "repo/include/GLFW/glfw3.h",
	    "repo/include/GLFW/glfw3native.h",
		"repo/src/glfw_config.h",
		"repo/src/context.c",
		"repo/src/init.c",
		"repo/src/input.c",
		"repo/src/monitor.c",

		"repo/src/null_init.c",
		"repo/src/null_joystick.c",
		"repo/src/null_monitor.c",
		"repo/src/null_window.c",

		"repo/src/platform.c",
		"repo/src/vulkan.c",
		"repo/src/window.c",
    }

    filter "system:linux"
        systemversion "latest"

        files{
            "repo/src/x11_init.c",
			"repo/src/x11_monitor.c",
			"repo/src/x11_window.c",
			"repo/src/xkb_unicode.c",
			"repo/src/posix_module.c",
			"repo/src/posix_time.c",
			"repo/src/posix_thread.c",
			"repo/src/posix_module.c",
			"repo/src/glx_context.c",
			"repo/src/egl_context.c",
			"repo/src/osmesa_context.c",
			"repo/src/linux_joystick.c"
        }

        defines{ "_GLFW_X11" }
    filter "system:macosx"

        files{
            "repo/src/cocoa_init.m",
			"repo/src/cocoa_monitor.m",
			"repo/src/cocoa_window.m",
			"repo/src/cocoa_joystick.m",
			"repo/src/cocoa_time.c",
			"repo/src/nsgl_context.m",
			"repo/src/posix_thread.c",
			"repo/src/posix_module.c",
			"repo/src/osmesa_context.c",
			"repo/src/egl_context.c"
        }

        defines{ "_GLFW_COCOA" }

    filter "system:windows"
        systemversion "latest"

        files{
            "repo/src/win32_init.c",
			"repo/src/win32_joystick.c",
			"repo/src/win32_module.c",
			"repo/src/win32_monitor.c",
			"repo/src/win32_time.c",
			"repo/src/win32_thread.c",
			"repo/src/win32_window.c",
			"repo/src/wgl_context.c",
			"repo/src/egl_context.c",
			"repo/src/osmesa_context.c"
        }

        defines{
            "_GLFW_WIN32", "_CRT_SECURE_NO_WARNINGS"
        }

	
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
