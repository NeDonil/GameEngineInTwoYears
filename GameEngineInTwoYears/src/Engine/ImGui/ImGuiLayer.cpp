#pragma once
#include <enpch.h>
#include "ImGuiLayer.h"

#include "imgui.h"
#include <examples/imgui_impl_opengl3.h>
#include <examples/imgui_impl_glfw.h>

#include "Engine/Core/Application.h"


#include "GLFW/glfw3.h"
#include "GLAD/glad.h"

namespace Engine
{
	ImGuiLayer::ImGuiLayer():
		Layer("ImGuiLayer")
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
	}

	ImGuiLayer::~ImGuiLayer()
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
	}

	void ImGuiLayer::OnAttach()
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();
		
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");

	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		if (m_BlockEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
			e.Handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
			e.Handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
		}
	}

	void ImGuiLayer::OnDetach()
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin()
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		//Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::OnImGuiRender()
	{
#ifdef ENABLE_PROFILING
		ENGINE_PROFILE_FUNCTION();
#endif
		static bool show = true;
		//ImGui::ShowDemoWindow(&show);
	}

}