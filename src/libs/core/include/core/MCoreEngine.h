#ifndef MASON_CORE_ENGINE_H
#define MASON_CORE_ENGINE_H

#include <string>
#include <memory>
#include <queue>

#include <win-export/WinExport.h>

#include "core/nlohmann/json.hpp"

#include "core/MEvent.h"

namespace mason {

class MGame;

class MASON_CORE_API MCoreEngine {
public:
    MCoreEngine();

    int exec(MGame *game);

private:
    void load_config(const nlohmann::json &cfg);
    bool load_game(MGame *game);

};

}

#endif
