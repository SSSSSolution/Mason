#ifndef MASON_CORE_ENGINE_H
#define MASON_CORE_ENGINE_H

#include <string>
#include <memory>

#include <win-export/WinExport.h>

#include "core/ILogicEngine.h"
#include "core/IRenderEngine.h"
#include "core/nlohmann/json.hpp"

namespace mason {

class MGame;

class MASON_CORE_API MCoreEngine {
public:
    MCoreEngine(const std::string &name);

    int exec(MGame *game);

private:
    void load_config(const nlohmann::json &cfg);
    bool load_game(MGame *game);

private:
    std::string m_name;
    std::string m_logic_engine_name = "";
    std::string m_render_engine_name = "";

    std::unique_ptr<ILogicEngine> m_logic_engine;
    std::unique_ptr<IRenderEngine> m_render_engine;
};

}

#endif
