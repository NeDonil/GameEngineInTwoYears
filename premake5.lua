workspace "GameEngineInTwoYears"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

configurations
{
	"Debug",
	"Release"
}

architecture "x64"

include "GameEngineInTwoYears/vendor/ImGui"
include "GameEngineInTwoYears/vendor/GLFW"
include "GameEngineInTwoYears/vendor/Glad"
include "GameEngineInTwoYears/vendor/box2d"

IncludeDir = {}
IncludeDir["GLFW"] = "GameEngineInTwoYears/vendor/GLFW/include"
IncludeDir["Glad"] = "GameEngineInTwoYears/vendor/GLAD/include"
IncludeDir["ImGui"] = "GameEngineInTwoYears/vendor/ImGui/"
IncludeDir["glm"] = "GameEngineInTwoYears/vendor/glm/"
IncludeDir["stb_image"] = "GameEngineInTwoYears/vendor/stb_image/"
IncludeDir["entt"] = "GameEngineInTwoYears/vendor/entt/include/"
IncludeDir["box2d"] = "GameEngineInTwoYears/vendor/box2d/include/"


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
			"%{prj.name}/vendor/glm/glm/**.inl",
			"%{prj.name}/vendor/stb_image/**.cpp",
			"%{prj.name}/vendor/stb_image/**.h",
			"Editor/src/**.h"
		}
	
		includedirs
		{
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include",
			"%{prj.name}/vendor/glm/",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.stb_image}",
			"%{IncludeDir.entt}"
	
		}
	
		links
		{
			"GLFW",
			"Glad",
			"ImGui",
			"box2d",
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
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.box2d}",
		"GameEngineInTwoYears/src"
	}

	links
	{
		"GameEngineInTwoYears",
		"Glad",
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


project "Editor"
	location "Editor"
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
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"GameEngineInTwoYears/src",
		"%{IncludeDir.entt}"
	}

	links
	{
		"GameEngineInTwoYears",
		"Glad",
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