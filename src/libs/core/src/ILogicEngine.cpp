#include "core/ILogicEngine.h"
#include "LogicEngine.h"

namespace mason {
    std::unique_ptr<ILogicEngine> LogicEngineFactory::create(const std::string &name) {
        if (name == "default") {
            return std::make_unique<LogicEngine>();
        }
        return nullptr;
    }
}