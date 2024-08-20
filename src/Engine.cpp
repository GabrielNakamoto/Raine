#include "Engine.h"
#include "Common.h"
#include "Gui.h"
#include "BackEnd/BackEnd.h"
#include "Renderer/Renderer.h"
#include "Input/Input.h"

#include "testState.h"

float deltaTime = 0.0f;
float lastFrame = 0.0f;

namespace Engine {

    void Run()
    {

        BackEnd::Init(SCR_WIDTH, SCR_HEIGHT, "Raine Engine");
        Gui::Init();

        testState* state = new testState();

        while(BackEnd::WindowIsOpen())
        {

            float currentFrame = glfwGetTime();
            deltaTime = lastFrame - currentFrame;
            lastFrame = currentFrame;

            BackEnd::BeginFrame();
            Input::Update();

            state->Update();

            Renderer::RenderFrame();

            /* Gui::BeginFrame(); */
            /* Gui::TestingWindow(); */
            /* Gui::RenderFrame(); */

            BackEnd::EndFrame();

        }
        delete state;
        BackEnd::Cleanup();

    }
}

