#pragma once

#include "Common.h"
#include "Shader.h"

class ShaderProgram {
private:
	unsigned int m_id;
public:
	ShaderProgram(Shader* vShader, Shader* fShader);

	void Use();
	unsigned int GetId();

	void SetMat4(const char* uniform, glm::mat4& value);
	void SetVec3(const char* uniform, glm::vec3& value);
    void SetInt(const char* uniform, int value);

	~ShaderProgram();
};
