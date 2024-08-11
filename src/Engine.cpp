#include "Engine.h"
#include "Common.h"
#include "Gui.h"
#include "BackEnd/BackEnd.h"
#include "Renderer/Renderer.h"
#include "Input/Input.h"

void Engine::Run(){

	BackEnd::Init(SCR_WIDTH, SCR_HEIGHT, "OpenGL");
    Renderer::Init();
    Gui::Init();

	while(BackEnd::WindowIsOpen()){

		BackEnd::BeginFrame();
        Input::Update();

        Renderer::RenderFrame();

        /* Gui::BeginFrame(); */
        /* Gui::TestingWindow(); */
        /* Gui::RenderFrame(); */

		BackEnd::EndFrame();

	}
	BackEnd::Cleanup();
    Renderer::Cleanup();

}
