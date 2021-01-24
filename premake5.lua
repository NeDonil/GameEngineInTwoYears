--main
workspace "GameEngineInTwoYears"
	architecture "x64"
	startproject "Editor"

configurations
{
	"Debug",
	"Release"
}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/GameEngineInTwoYears/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/GameEngineInTwoYears/vendor/GLAD/include"
IncludeDir["ImGui"] = "%{wks.location}/GameEngineInTwoYears/vendor/ImGui/"
IncludeDir["glm"] = "%{wks.location}/GameEngineInTwoYears/vendor/glm/"
IncludeDir["stb_image"] = "%{wks.location}/GameEngineInTwoYears/vendor/stb_image/"
IncludeDir["entt"] = "%{wks.location}/GameEngineInTwoYears/vendor/entt/include/"
IncludeDir["box2d"] = "%{wks.location}/GameEngineInTwoYears/vendor/box2d/include/"
IncludeDir["yaml_cpp"] = "%{wks.location}/GameEngineInTwoYears/vendor/yaml-cpp/include/"
IncludeDir["ImGuizmo"] = "%{wks.location}/GameEngineInTwoYears/vendor/ImGuizmo"

group "Deps"
	include "GameEngineInTwoYears/vendor/GLFW"
	include "GameEngineInTwoYears/vendor/GLAD"
	include "GameEngineInTwoYears/vendor/imgui"
	include "GameEngineInTwoYears/vendor/yaml-cpp"
	include "GameEngineInTwoYears/vendor/box2d"
group ""

include "GameEngineInTwoYears"
include "Sandbox"
include "Editor"