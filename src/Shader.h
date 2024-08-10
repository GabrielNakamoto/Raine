#pragma once

#include "Common.h"

enum shader_type {
	vertex,
	fragment
};

class Shader {
private:
	unsigned int m_id;
	std::string file_path;
	shader_type type;

public:
	Shader(std::string path, shader_type type);
	bool Compile();
	unsigned int GetId();
	~Shader();
};
