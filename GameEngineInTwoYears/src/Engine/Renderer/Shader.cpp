#include <enpch.h>
#include "Shader.h"
#include <GLAD/glad.h>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

std::string read_file(const char* path)
{
	std::ifstream ifs(path);
	std::string content(std::istreambuf_iterator<char>(ifs.rdbuf()), std::istreambuf_iterator<char>());
	return content;
}

namespace Engine
{
	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		m_RendererID = glCreateProgram();
		GLuint vertexShader, fragmentShader;

		const char* vertexSource   = vertexSrc.c_str();
		const char* fragmentSource = fragmentSrc.c_str();

		int status;
		char infolog[512];

		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, 0);
		glCompileShader(vertexShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
		
		if (!status)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
			ENGINE_CORE_CRITICAL("Vertex Shader Error: \n {0}", infolog);
		}

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, 0);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);

		if (!status)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
			ENGINE_CORE_CRITICAL("Fragment Shader Error: \n {0}", infolog);
		}

		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);
		glLinkProgram(m_RendererID);

		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}
