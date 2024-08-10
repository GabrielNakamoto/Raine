#include "BackEnd.h"

namespace BackEnd {

	GLFWwindow* _window = NULL;
	/* GLFWmonitor* _monitor = NULL; */

	void Init(int width, int height, std::string title){
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
		/* _monitor = glfwGetPrimaryMonitor(); */
		_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (_window == NULL) {
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(_window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}

        glEnable(GL_DEPTH_TEST);
	}

	bool WindowIsOpen(){
		return !glfwWindowShouldClose(_window);
	}

	GLFWwindow* GetWindowPointer(){
		return _window;
	}

	void SetWindowShouldClose(bool value){
		glfwSetWindowShouldClose(_window, value);
	}

	void BeginFrame(){
		glfwPollEvents();
	}

	void EndFrame(){
		glfwSwapBuffers(_window);
	}

	void Cleanup(){
		glfwTerminate();
	}
}


