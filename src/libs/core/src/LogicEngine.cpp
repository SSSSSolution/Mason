#include "LogicEngine.h"

#include <chrono>
#include <thread>

#include "core/MLog.h"
#include "core/MGame.h"
#include "core/MEventBus.h"

namespace mason {

    void LogicEngine::initialize() {
        MInfo("LogicEngine::initialize()");
    }

    void LogicEngine::deinitialize() {
        MInfo("LogicEngine::deinitialize()");
    }

    void LogicEngine::start() {
        MInfo("LogicEngine::start()");
    }

    void LogicEngine::pause() {
        MInfo("LogicEngine::pause()");
    }

    void LogicEngine::stop() {
        MInfo("LogicEngine::stop()");
    }

    void LogicEngine::exec() {
        MInfo("LogicEngine::exec()");
        mBus.post_event_to_logic(std::make_shared<MEvent>(MEvent::Type::MAppStart));

        const std::chrono::microseconds frame_duration(33333);
        auto last_time = std::chrono::high_resolution_clock::now();

        while (true) {
            auto current_time = std::chrono::high_resolution_clock::now();
            auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(current_time - last_time);
            last_time = current_time;

            // send event to game
            {
                std::queue<std::shared_ptr<MEvent>> event_queue;
                mBus.take_event_queue_from_logic(event_queue);
                auto event_dispatcher = m_game->get_event_dispatcher();
                while (!event_queue.empty()) {
                    auto event = event_queue.front();
                    event_queue.pop();
                    event_dispatcher->dispatch_event(event);
                }
            }

            auto next_time = current_time + frame_duration;
            while (std::chrono::high_resolution_clock::now() < next_time) {
//                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                ;
            }
        }
    }

    void LogicEngine::on_event(std::shared_ptr<MEvent> event) {
        switch (event->type()) {
            case MEvent::Type::MAppStart:
                start();
                break;
            default:
                break;

        }
    }
}