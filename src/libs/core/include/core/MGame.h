#ifndef MASON_GAME_H
#define MASON_GAME_H

#include <memory>
#include <vector>

namespace mason {

class MGameScene;
class EventBus;

class MGame {
public:
    MGame() = default;
    virtual ~MGame() = default;

    std::shared_ptr<MGameScene> current_scene() const;

    bool add_scene(std::shared_ptr<MGameScene> scene);

    void set_current_scene(int index);

    virtual void on_start() = 0;
    virtual void on_pause() = 0;
    virtual  void on_finished() = 0;

protected:
    virtual void on_scene_start(int index) = 0;
    virtual void on_scene_finished(int index) = 0;

private:
    std::vector<std::shared_ptr<MGameScene>> m_scenes;
    int m_current_scene_idx = 0;

    std::shared_ptr<EventBus> m_event_bus;

    friend class ILogicEngine;
    friend class IRenderEngine;
};

}

#endif
