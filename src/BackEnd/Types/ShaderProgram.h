#pragma once

#include "../../Common.h"
#include "../../Renderer/RendererCommon.h"
#include "Shader.h"

class ShaderProgram {
private:
    // shader vector?
	unsigned int m_id;
    Shader* m_vShader;
    Shader* m_fShader;

    void Link();
public:
	ShaderProgram(Shader* vShader, Shader* fShader);

	void Use();
    void Reload();

	unsigned int GetId();

	void SetMat4(const char* uniform, glm::mat4& value);
	void SetVec3(const char* uniform, glm::vec3& value);
    void SetInt(const char* uniform, int value);

	~ShaderProgram();
};
