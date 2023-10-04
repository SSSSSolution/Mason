#include "core/MOcTree.h"
#include "core/MLog.h"

namespace mason {

MOcTreeNode::MOcTreeNode(const MAABBox &bounds) :
    m_bounds(bounds){

}

bool MOcTreeNode::insert(MOcTreeItem *item) {
    if (!m_bounds.intersects(item->get_bounds())) {
        return false;
    }

    if (item->get_bounds().contains(m_bounds) || !can_fit_in_any_child(item->get_bounds())) {
        MDebug("insert a item to " + m_bounds.str());
        m_items.push_back(item);
        return true;
    }

    if (m_children[0] != nullptr || subdivide()) {
        for (int i = 0; i < 8; i++) {
            if (m_children[i]->insert(item)) {
                return true;
            }
        }
    } else {
        MDebug("insert a item to " + m_bounds.str());
        m_items.push_back(item);
        return true;
    }

    return false;
}

void MOcTreeNode::remove(mason::MOcTreeItem *item) {
    if (!m_bounds.intersects(item->get_bounds())) {
        return;
    }

    if (m_children[0] != nullptr) {
        for (int i = 0; i < 8; i++) {
            m_children[i]->remove(item);
        }
    } else {
        auto it = std::find(m_items.begin(), m_items.end(), item);
        if (it != m_items.end()) {
            m_items.erase(it);
        }
    }
}

std::vector<MOcTreeItem *> MOcTreeNode::queryIntersect(const MAABBox &bounds) const {
    std::vector<MOcTreeItem *> intersect_items;

    if (!m_bounds.intersects(bounds)) {
        return intersect_items;
    }

    for (auto item : m_items) {
        if (item->get_bounds().intersects(bounds)) {
            intersect_items.push_back(item);
        }
    }

    if (m_children[0] != nullptr) {
        for (int i = 0; i < 8; i++) {
            auto child_intersect_items = m_children[i]->queryIntersect(bounds);
            intersect_items.insert(intersect_items.end(), child_intersect_items.begin(), child_intersect_items.end());
        }
    }

    return intersect_items;
}

bool MOcTreeNode::subdivide() {
    if (m_children[0] != nullptr) {
        return false;
    }

    if (m_bounds.max.x - m_bounds.min.x < 0.0001) {
        return false;
    }

    MTrace("divide a node");

    MAABBox child_bounds[8];
    calculate_child_bounds(child_bounds);

    for (int i = 0; i < 8; i++) {
        m_children[i] = new MOcTreeNode(child_bounds[i]);
    }

    return true;
}

bool MOcTreeNode::can_fit_in_any_child(const MAABBox &bounds) const{
    MAABBox child_bounds[8];
    calculate_child_bounds(child_bounds);

    for (int i = 0; i < 8; i++) {
        if (child_bounds[i].contains(bounds)) {
            return true;
        }
    }

    return false;
}

void MOcTreeNode::calculate_child_bounds(MAABBox *child_bounds) const {
    float midX = (m_bounds.min.x + m_bounds.max.x) / 2.0f;
    float midY = (m_bounds.min.y + m_bounds.max.y) / 2.0f;
    float midZ = (m_bounds.min.z + m_bounds.max.z) / 2.0f;

    child_bounds[0] = MAABBox(m_bounds.min, Vector3f(midX, midY, midZ));
    child_bounds[1] = MAABBox(Vector3f(midX, m_bounds.min.y, m_bounds.min.z), Vector3f(m_bounds.max.x, midY, midZ));
    child_bounds[2] = MAABBox(Vector3f(midX, midY, m_bounds.min.z), Vector3f(m_bounds.max.x, m_bounds.max.y, midZ));
    child_bounds[3] = MAABBox(Vector3f(m_bounds.min.x, midY, m_bounds.min.z), Vector3f(midX, m_bounds.max.y, midZ));
    child_bounds[4] = MAABBox(Vector3f(m_bounds.min.x, m_bounds.min.y, midZ), Vector3f(midX, midY, m_bounds.max.z));
    child_bounds[5] = MAABBox(Vector3f(midX, m_bounds.min.y, midZ), Vector3f(m_bounds.max.x, midY, m_bounds.max.z));
    child_bounds[6] = MAABBox(Vector3f(midX, midY, midZ), m_bounds.max);
    child_bounds[7] = MAABBox(Vector3f(m_bounds.min.x, midY, midZ), Vector3f(midX, m_bounds.max.y, m_bounds.max.z));
}

}