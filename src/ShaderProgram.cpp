#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(Shader* vShader, Shader* fShader){
	m_id = glCreateProgram();
	glAttachShader(m_id, vShader->GetId());
	glAttachShader(m_id, fShader->GetId());
	glLinkProgram(m_id);

	int success;
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);

	if(!success){
		char infoLog[512];
		glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
		std::cout << "Error linking shader program info:\n" << infoLog << std::endl;
	}
}

void ShaderProgram::Use(){
	glUseProgram(m_id);
}

unsigned int ShaderProgram::GetId(){
	return m_id;
}

void ShaderProgram::SetMat4(const char* uniform, glm::mat4& value){
        unsigned int u_id = glGetUniformLocation(m_id, uniform);
        glUniformMatrix4fv(u_id, 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::SetVec3(const char* uniform, glm::vec3& value){
        unsigned int u_id = glGetUniformLocation(m_id, uniform);
        glUniform3fv(u_id, 1, glm::value_ptr(value));
}

void ShaderProgram::SetInt(const char* uniform, int value){
        glUniform1i(glGetUniformLocation(m_id, uniform), value);
}

ShaderProgram::~ShaderProgram(){
	glDeleteProgram(m_id);
}
