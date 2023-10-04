#include "core/MApp.h"
#include "core/MCoreEngine.h"
#include "core/MGame.h"
#include "core/MGameScene.h"

#include "items/GroundItem.h"

using namespace mason;

class JTWGame : public MGame {
public:
    JTWGame() {
        m_first_chapter_scene = std::make_shared<MGameScene>("JTW-first-chapter", "C:\\tmp\\JTW_LOCAL\\scenes\\first-chapter\\scene.json");

        MItemFactory::get_instance().register_item_type("GroundItem", []() {
            return std::make_unique<GroundItem>();
        });
    }

    ~JTWGame() {

    }

    void on_start() override {
        MInfo("JTW Game Start");
        m_first_chapter_scene->load();
    }

    void on_pause() override {
        MInfo("JTW Game Pause");
    }

    void on_finish() override {
        MInfo("JTW Game Finish");
    }

    void on_scene_start(int index) {
        MInfo("JTW Scene Start");
    }

    void on_scene_finished(int index) {
        MInfo("JTW Scene Finished");
    }

private:
    std::shared_ptr<MGameScene> m_first_chapter_scene;
};

int main(int argc, char **argv) {
    MApp &app = MApp::instance(argc, argv, "JourneyToWest");

    MCoreEngine engine;

    JTWGame game;

    return engine.exec(&game);
}