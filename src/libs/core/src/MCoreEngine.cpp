#include "core/MCoreEngine.h"
#include "core/MApp.h"

#include <thread>

namespace mason {

    MCoreEngine::MCoreEngine(const std::string &name): m_name(name) {
        load_config(mApp.get_config());
    }

    int MCoreEngine::exec(MGame *game) {
        m_logic_engine = LogicEngineFactory::create(m_logic_engine_name);
        if (!m_logic_engine) {
            MFatal("create logic engine failed");
            return -1;
        }

        m_render_engine = RenderEngineFactory::create(m_render_engine_name);
        if (!m_render_engine) {
            MFatal("create render engine failed");
            return -1;
        }

        if (!load_game(game)) {
            MFatal("load game script failed");
            return -1;
        }

        std::thread logic_thread([this](){
            m_logic_engine->start();
        });

        std::thread render_thread([this](){
            m_render_engine->start();
        });

        logic_thread.join();
        render_thread.join();

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
            for (auto &core_cfg: cfg["core_engine"]) {
                if (core_cfg.contains("name") && to_string(core_cfg["name"]) == m_name) {
                    if (core_cfg.contains("logic_engine"))
                        m_logic_engine_name = to_string(core_cfg["logic_engine"]);
                    if (core_cfg.contains("render_engine"))
                        m_render_engine_name = to_string(core_cfg["render_engine"]);
                    break;
                }
            }
        }

        if (m_logic_engine_name.empty()) {
            MWarning("logic_engine is not set in config, use default");
            m_logic_engine_name = "default";
        }

        if (m_render_engine_name.empty()) {
            MWarning("render_engine is not set in config, use default");
            m_render_engine_name = "default";
        }
    }
}