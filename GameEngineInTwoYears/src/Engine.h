#pragma once

//For use by Applications
#include "Engine/Core/Application.h"
#include "Engine/Core/Log.h"
#include "Engine/Core/Layer.h"

#include "Engine/Core/Input.h"
#include "Engine/Core/KeyCodes.h"
#include "Engine/Core/MouseButtonKeyCodes.h"
#pragma once 

#include "Engine/ImGui/ImGuiLayer.h"
//---------Renderer--------------------------------
#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/RenderCommand.h"

#include "Engine/Renderer/Buffer.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/Texture.h"
#include "Engine/Renderer/VertexArray.h"

#include "Engine/Core/Timestep.h"

#include "Engine/Renderer/Renderer2D.h"
#include "Engine/Renderer/OrthographicCamera.h"
#include "Engine/Renderer/OrthographicCameraController.h"

//-------------------------------------------------
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

//---------OpenGL----------------------------------
#include "Platform/OpenGL/OpenGLShader.h"