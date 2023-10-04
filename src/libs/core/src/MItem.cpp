#include "core/MItem.h"
#include <atomic>

namespace mason {

MItem::MItem() {
    static std::atomic<uint32_t> s_item_id(0);
    m_id = s_item_id++;
}

void MItem::load_from_json(const nlohmann::json &json) {
    if (json.contains("custom")) {
        load_custom_data(json["custom"]);
    }
}

MItemFactory &MItemFactory::get_instance() {
    static MItemFactory instance;
    return instance;
}

bool MItemFactory::register_item_type(const std::string &type_name, std::function<std::unique_ptr<MItem>()> create_func) {
    if (m_item_creators.find(type_name) == m_item_creators.end()) {
        m_item_creators[type_name] = create_func;
        return true;
    }
    return false;
}

std::unique_ptr<MItem> MItemFactory::create_item(const std::string &type_name) {
    auto it = m_item_creators.find(type_name);
    if (it != m_item_creators.end()) {
        return it->second();
    }
    return nullptr;
}


}