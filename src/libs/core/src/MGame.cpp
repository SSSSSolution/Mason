#include "core/MGame.h"

#include "LogicEngine.h"
#include "RenderEngine.h"
#include "core/MGameScene.h"

namespace mason {

MGame::MGame() {
    m_event_dispatcher = std::make_unique<GameEventDispatcher>(this);
}

void MGame::load_scene(std::shared_ptr<MGameScene> scene) {
    m_current_scene = scene;
}

// GameEventDispatcher
void GameEventDispatcher::dispatch_event(std::shared_ptr<MEvent> event) {
    switch (event->type()) {
        case MEvent::Type::MAppStart:
            m_game->on_start();
            break;
        case MEvent::Type::MAppPause:
            m_game->on_pause();
            break;
        case MEvent::Type::MAppFinish:
            m_game->on_finish();
            break;
        default:
            break;
    }
}


}
