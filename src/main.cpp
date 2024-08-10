#include "BackEnd.h"
#include "Renderer.h"

int main(){
	BackEnd::Init(SCR_WIDTH, SCR_HEIGHT, "OpenGL");
    Renderer::Init();

	while(BackEnd::WindowIsOpen()){

		BackEnd::BeginFrame();

        Renderer::RenderFrame();

		BackEnd::EndFrame();

	}
	BackEnd::Cleanup();
    Renderer::Cleanup();
	return 0;

}
