#include "ShaderProgram.h"
#include <iostream>

namespace Renderer
{
	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
	{
		GLuint vertexSHaderID;
		if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexSHaderID))
		{
			std::cerr << "VERTEX SHADER Compile-time error" << std::endl;
			return;
		}

		GLuint fragmentSHaderID;
		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentSHaderID))
		{
			std::cerr << "FRAGMENT SHADER Compile-time error" << std::endl;
			glDeleteShader(vertexSHaderID);
			return;
		}

		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexSHaderID);
		glAttachShader(m_ID, fragmentSHaderID);
		glLinkProgram(m_ID);

		/* Проверка, слинковалось ли всё корректно или нет -->  glLinkProgram(m_ID); */
		GLint success;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLchar infolog[1024];
			glGetShaderInfoLog(m_ID, 1024, nullptr, infolog);
			std::cerr << "ERROR::SHADER: Link-time error:\n" << infolog << std::endl;
		}
		else 
			m_isCompiled = true;

		glDeleteShader(vertexSHaderID);
		glDeleteShader(fragmentSHaderID);
	}

	bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
	{
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar infolog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, infolog);
			std::cerr << "ERROR::SHADER: Compile-time error:\n" << infolog << std::endl;
			return false;
		}
		return true;
	}

	void ShaderProgram::use() const
	{
		glUseProgram(m_ID);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_ID);
	}

	ShaderProgram& ShaderProgram::operator = (ShaderProgram&& shaderProgram) noexcept
	{
		glDeleteProgram(m_ID);
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.m_ID = 0;
		shaderProgram.m_isCompiled = false;
		return *this;
	}
	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
	{
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.m_ID = 0;
		shaderProgram.m_isCompiled = false;
	}
}