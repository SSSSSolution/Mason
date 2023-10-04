#ifndef MASON_GAME_H
#define MASON_GAME_H

#include <memory>
#include <vector>

#include "core/MEvent.h"
#include "core/IEventDispatcher.h"

#include "win-export/WinExport.h"

namespace mason {

class MGameScene;
class LogicEngine;
class RenderEngine;

class MASON_CORE_API MGame {
public:
    MGame();
    virtual ~MGame() = default;

//    void load(std::filesystem::path game_path){}

    IEventDispatcher *get_event_dispatcher() { return m_event_dispatcher.get(); }

    std::shared_ptr<MGameScene> current_scene() const;

    void load_scene(std::shared_ptr<MGameScene> scene);

    void set_current_scene(int index);

    virtual void on_start() = 0;
    virtual void on_pause() = 0;
    virtual  void on_finish() = 0;

protected:
    virtual void on_scene_start(int index) = 0;
    virtual void on_scene_finished(int index) = 0;

private:
    LogicEngine *m_logic_engine;
    RenderEngine *m_render_engine;

    std::shared_ptr<MGameScene> m_current_scene;

    std::vector<std::shared_ptr<MGameScene>> m_scenes;
    int m_current_scene_idx = 0;

    std::unique_ptr<IEventDispatcher> m_event_dispatcher;

    friend class GameEventDispatcher;

    friend class ILogicEngine;
    friend class IRenderEngine;
};

class GameEventDispatcher : public IEventDispatcher {
public:
    GameEventDispatcher(MGame *game) : m_game(game) {}
    void dispatch_event(std::shared_ptr<MEvent> event) override;

private:
    MGame *m_game;
};

}

#endif
