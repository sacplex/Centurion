workspace "Centurion"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Centurion"
	location "Centurion"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ctnpch.h"
	pchsource "Centurion/src/ctnpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"CTN_PLATFORM_WINDOWS",
			"CTN_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "CTN_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "CTN_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "CTN_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Centurion/vendor/spdlog/include",
		"Centurion/src"
	}

	links
	{
		"Centurion"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"CTN_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CTN_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "CTN_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "CTN_DIST"
		optimize "On"