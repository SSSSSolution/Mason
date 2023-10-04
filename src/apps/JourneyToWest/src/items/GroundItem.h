#ifndef JTW_GROUND_ITEM_H
#define JTW_GROUND_ITEM_H

#include <core/MItem.h>
#include <vector>

#include "core/MVector.h"


struct TerrainBlock {
    std::vector<float> height_map;
    int size_point; // the number of points in the height map's each side
    float resolution; // the distance between two points in the height map
    std::vector<mason::Vector3f> normals;

    float get_height(int x, int y) const;
};

class GroundItem : public mason::MItem {
public:
    GroundItem();
    virtual ~GroundItem() = default;

    virtual void load_custom_data(const nlohmann::json &json) override;

private:
    int m_side;
    int m_x;
    int m_y;
    TerrainBlock m_terrain_block;
};

#endif
