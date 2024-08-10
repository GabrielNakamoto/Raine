#include "Shader.h"
#include "Util.hpp"

Shader::Shader(std::string path, shader_type type) : file_path(path), type(type) {}

bool Shader::Compile(){
	std::string contents = Util::ReadFile(file_path);
	const char* source = contents.c_str();

	GLenum gl_type = type == vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;

	m_id = glCreateShader(gl_type);
	glShaderSource(m_id, 1, &source, NULL);
	glCompileShader(m_id);

	int success;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(m_id, 512, nullptr, infoLog);
		std::cout << "Error: " << gl_type << " failed compilation at file path: " << file_path << "\n" << infoLog << std::endl;
        exit(1);
	} else {
        std::string filename = file_path.substr(file_path.find_last_of("/") + 1);
        std::cout << "Compiled shader " << filename << std::endl;
    }
	return success;
}

unsigned int Shader::GetId(){
	return m_id;
}

Shader::~Shader(){
	glDeleteShader(m_id);
}
