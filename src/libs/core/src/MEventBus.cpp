#include "core/MEventBus.h"

namespace mason {

MEventBus &MEventBus::get_instance() {
    static MEventBus instance;
    return instance;
}

// Logic Queue
void MEventBus::post_event_to_logic(std::shared_ptr<MEvent> event) {
    std::lock_guard<std::mutex> lock(m_logic_event_queue_mutex);
    m_logic_event_queue.push(event);
}

void MEventBus::take_event_queue_from_logic(std::queue<std::shared_ptr<MEvent>> &queue) {
    std::lock_guard<std::mutex> lock(m_logic_event_queue_mutex);
    queue.swap(m_logic_event_queue);
}

void MEventBus::clear_logic_event_queue() {
    std::lock_guard<std::mutex> lock(m_logic_event_queue_mutex);
    std::queue<std::shared_ptr<MEvent>> empty;
    m_logic_event_queue.swap(empty);
}

// Render Queue
void MEventBus::post_event_to_render(std::shared_ptr<MEvent> event) {
    std::lock_guard<std::mutex> lock(m_render_event_queue_mutex);
    m_render_event_queue.push(event);
}

void MEventBus::take_event_queue_from_render(std::queue<std::shared_ptr<MEvent>> &queue){
    std::lock_guard<std::mutex> lock(m_render_event_queue_mutex);
    queue.swap(m_render_event_queue);
}

void MEventBus::clear_render_event_queue() {
    std::lock_guard<std::mutex> lock(m_render_event_queue_mutex);
    std::queue<std::shared_ptr<MEvent>> empty;
    m_render_event_queue.swap(empty);
}

}
