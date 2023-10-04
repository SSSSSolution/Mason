#ifndef MASON_CORE_LOGIC_ENGINE_H
#define MASON_CORE_LOGIC_ENGINE_H

#include <memory>
#include <queue>
#include <mutex>

#include "core/MEvent.h"

namespace mason {

class MGame;

class LogicEngine {
public:
    LogicEngine(MGame *game): m_game(game) {}

    void initialize();

    void deinitialize();

    void start();

    void pause();

    void stop();

    void exec();

private:
    void on_event(std::shared_ptr<MEvent> event);

private:
    MGame *m_game;
};

}

#endif

