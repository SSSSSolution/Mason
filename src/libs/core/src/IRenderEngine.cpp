#include "core/IRenderEngine.h"

#include "RenderEngine.h"

namespace mason {
    std::unique_ptr<IRenderEngine> RenderEngineFactory::create(const std::string &name) {
        if (name == "default") {
            return std::make_unique<RenderEngine>();
        }
        return nullptr;
    }
}
