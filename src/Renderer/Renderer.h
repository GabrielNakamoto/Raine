#pragma once

#include "../Common.h"
#include "Types/Model.h"

namespace Renderer {
	void RenderFrame();
    void AddModel(std::shared_ptr<Model> model);
}
