#ifndef MASON_CORE_MITEM_H
#define MASON_CORE_MITEM_H

#include <filesystem>
#include <map>

#include "core/nlohmann/json.hpp"
#include "MOcTree.h"

#include "win-export/WinExport.h"

namespace mason {

class MASON_CORE_API RenderData {

};

class MASON_CORE_API MItem : public MOcTreeItem {
public:
    MItem();
    virtual ~MItem() = default;

    uint32_t get_id() const { return m_id; }

    void load_from_json(const nlohmann::json &json);

    virtual const MAABBox &get_bounds() const override { return m_bounds; }

    RenderData *get_render_data() { return &m_render_data; }

protected:
    virtual void load_custom_data(const nlohmann::json &json) {};

protected:
    MAABBox m_bounds;
    bool m_collidable = true;

private:
    uint32_t m_id;


    RenderData m_render_data;

    // transform
    Vector3f m_position;

    // physics properties
    float m_mass;
    float m_velocity;
    float m_acceleration;

    bool visibility;
};

class MASON_CORE_API MItemFactory {
public:
//    using CreateItemFunc = std::function<std::unique_ptr<MItem>()>;
    static MItemFactory &get_instance();

    bool register_item_type(const std::string &type_name, std::function<std::unique_ptr<MItem>()> create_func);

    std::unique_ptr<MItem> create_item(const std::string &type_name);

private:
    MItemFactory() = default;
    std::map<std::string, std::function<std::unique_ptr<MItem>()>> m_item_creators;
};

}

#endif
