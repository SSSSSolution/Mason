#ifndef MASON_CORE_MGAME_SCENE_H
#define MASON_CORE_MGAME_SCENE_H

#include <string>
#include <filesystem>
#include <memory>

#include "core/MOcTree.h"
#include "core/MItem.h"
#include "win-export/WinExport.h"

namespace mason {

class MASON_CORE_API MGameScene {
public:
    MGameScene(std::string name, std::filesystem::path scene_path);
    virtual ~MGameScene() = default;

    void load();

protected:
    std::string m_name;
    std::filesystem::path m_scene_path;

    std::map<uint32_t, std::unique_ptr<MItem>> m_items_store;
    std::unique_ptr<MOcTreeNode> m_item_tree;
};

}

#endif
