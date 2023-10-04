#ifndef MASON_CORE_RENDER_ENGINE_H
#define MASON_CORE_RENDER_ENGINE_H

namespace mason {

class MGame;

class RenderEngine {
public:
    RenderEngine(MGame *game): m_game(game) {}

    void initialize();
    void deinitialize();

    void start();
    void pause();
    void stop();

private:
    MGame *m_game;
};

}

#endif
