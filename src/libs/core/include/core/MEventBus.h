#ifndef MASON_CORE_MEVENT_BUS_H
#define MASON_CORE_MEVENT_BUS_H

#include <mutex>
#include <memory>
#include <queue>

#include "core/MEvent.h"
#include "win-export/WinExport.h"

#define mBus mason::MEventBus::get_instance()

namespace mason {

class MASON_CORE_API MEventBus {
public:
    static MEventBus &get_instance();

    void post_event_to_logic(std::shared_ptr<MEvent> event);
    void take_event_queue_from_logic(std::queue<std::shared_ptr<MEvent>> &queue);
    void clear_logic_event_queue();

    void post_event_to_render(std::shared_ptr<MEvent> event);
    void take_event_queue_from_render(std::queue<std::shared_ptr<MEvent>> &queue);
    void clear_render_event_queue();

private:
    MEventBus() = default;
    ~MEventBus() = default;

private:
    std::mutex m_logic_event_queue_mutex;
    std::queue<std::shared_ptr<MEvent>> m_logic_event_queue;

    std::mutex m_render_event_queue_mutex;
    std::queue<std::shared_ptr<MEvent>> m_render_event_queue;
};

}

#endif
