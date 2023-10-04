#include "core/MGameScene.h"

#include <fstream>

#include "core/MLog.h"
#include "core/nlohmann/json.hpp"

namespace mason {

static bool read_json_file(std::filesystem::path path, nlohmann::json &json) {
    std::ifstream json_file(path);
    if (!json_file.is_open()) {
        MError("failed to open file: " + path.string());
        return false;
    }

    try {
        json_file >> json;
    } catch (const nlohmann::json::parse_error &e) {
        MError("failed to parse json file: " + path.string());
        MError(e.what());
        return false;
    }

    return true;
}

MGameScene::MGameScene(std::string name, std::filesystem::path scene_path):
    m_name(name), m_scene_path(scene_path) {
    MAABBox bounds(Vector3f(-100, -100, -100), Vector3f(100, 100, 100));
    m_item_tree = std::make_unique<MOcTreeNode>(bounds);
}

void MGameScene::load() {
    MInfo("load scene: " + m_scene_path.string());
    nlohmann::json scene_json;
    if (!read_json_file(m_scene_path, scene_json)) {
        MError("failed to load scene: " + m_scene_path.string());
        return;
    }

    for (auto &item_path : scene_json["items"]) {
        nlohmann::json item_json;
        if (!read_json_file(m_scene_path.parent_path() / item_path.get<std::string>(), item_json)) {
            MError("failed to load item: " + item_path.get<std::string>());
            continue;
        }

        if (!item_json.contains("type")) {
            MError("item json does not contain type: " + item_path.get<std::string>());
            continue;
        }

        std::string item_type = item_json["type"];
        std::unique_ptr<MItem> item = MItemFactory::get_instance().create_item(item_type);
        if (!item) {
            MError("failed to create item: " + item_type);
            continue;
        }

        MInfo("add item: " + item_type);
        item->load_from_json(item_json);
        m_item_tree->insert(item.get());
        m_items_store[item->get_id()] = std::move(item);
    }
}


}