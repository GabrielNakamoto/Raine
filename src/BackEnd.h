#pragma once

#include "Common.h"

namespace BackEnd {

	void Init(int width, int height, std::string title);
	bool WindowIsOpen();
	GLFWwindow* GetWindowPointer();
	void SetWindowShouldClose(bool value);
	void BeginFrame();
	void EndFrame();
	void Cleanup();
}

