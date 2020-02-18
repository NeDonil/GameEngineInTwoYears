workspace "GameEngineInTwoYears"

architecture "x64"

configurations
{
	"Debug",
	"Release"
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "GameEngineInTwoYears/vendor/GLFW/include"
IncludeDir["Glad"] = "GameEngineInTwoYears/vendor/GLAD/include"
IncludeDir["ImGui"] = "GameEngineInTwoYears/vendor/ImGui/"

include "GameEngineInTwoYears/vendor/GLFW"
include "GameEngineInTwoYears/vendor/Glad"
include "GameEngineInTwoYears/vendor/ImGui"

project "GameEngineInTwoYears"
location "GameEngineInTwoYears"

kind "StaticLib"
staticruntime "on"

language "C++"
cppdialect "C++17"

targetdir ("bin/" .. outputdir .. "/%{prj.name}")
objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "enpch.h"
	pchsource "GameEngineInTwoYears/src/enpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/glm/",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"

	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ENGINE_PLATFORM_WINDOWS",
			"ENGINE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "ENGINE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ENGINE_RELEASE"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"GameEngineInTwoYears/vendor/spdlog/include",
		"GameEngineInTwoYears/vendor/glm",
		"%{IncludeDir.ImGui}",
		"GameEngineInTwoYears/src"
	}

	links
	{
		"GameEngineInTwoYears",
		"ImGui"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ENGINE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ENGINE_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "ENGINE_RELEASE"
		optimize "on"

