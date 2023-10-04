#include "GroundItem.h"
#include "core/MVector.h"
#include "core/MLog.h"

using namespace mason;

float TerrainBlock::get_height(int x, int y) const {
    if (x < 0 || x >= size_point || y < 0 || y >= size_point) {
        MWarning("Invalid height map index: " + std::to_string(x) + ", " + std::to_string(y));
        return 0.0f;
    }

    return height_map[x * size_point + y];
}

GroundItem::GroundItem() {
    m_collidable = false;
}

void GroundItem::load_custom_data(const nlohmann::json &json) {
    m_side = json["side"];
    m_x = json["x"];
    m_y = json["y"];

    m_bounds = MAABBox(Vector3f(m_x - m_side / 2.0f, m_y - m_side / 2.0f, -1.01f),
                       Vector3f(m_x + m_side / 2.0f, m_y + m_side / 2.0f, -0.99f));

    // todo: load terrain block
}