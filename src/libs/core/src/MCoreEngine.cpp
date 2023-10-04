#include "core/MCoreEngine.h"

#include <thread>

#include "core/MApp.h"
#include "LogicEngine.h"
#include "RenderEngine.h"

namespace mason {

    MCoreEngine::MCoreEngine() {
          load_config(mApp.get_config());
    }

    int MCoreEngine::exec(MGame *game) {
        MInfo("CoreEngine exec()");
        if (!load_game(game)) {
            MFatal("load game script failed");
            return -1;
        }

        auto logic_engine = new LogicEngine(game);
        std::thread logic_thread([logic_engine](){
            MInfo("LogicEngine start");
            logic_engine->exec();
        });

        auto render_engine = new RenderEngine(game);
        std::thread render_thread([render_engine](){
            render_engine->start();
        });

        logic_thread.join();
        render_thread.join();

        delete render_engine;
        delete logic_engine;

        return 0;
    }

    bool MCoreEngine::load_game(MGame *game) {
        if (!game) {
            return false;
        }
        // todo: load game into logic engine

        return true;
    }

    void MCoreEngine::load_config(const nlohmann::json &cfg) {
        if (cfg.contains("core_engine")) {
            ;
        }
    }
}