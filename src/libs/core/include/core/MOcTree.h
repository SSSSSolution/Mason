#ifndef MASON_CORE_MOCTREE_H
#define MASON_CORE_MOCTREE_H

#include <vector>

#include "core/MAABBox.h"
#include "win-export/WinExport.h"

namespace mason {

struct MASON_CORE_API MOcTreeItem {
    virtual ~MOcTreeItem() = default;
    virtual const MAABBox &get_bounds() const = 0;
};


class MASON_CORE_API MOcTreeNode {
public:
    MOcTreeNode(const MAABBox &bounds);
    virtual ~MOcTreeNode() = default;

    bool insert(MOcTreeItem *item);
    void remove(MOcTreeItem *item);

    std::vector<MOcTreeItem *> queryIntersect(const MAABBox &bounds) const;


private:
    bool subdivide();

    bool can_fit_in_any_child(const MAABBox &bounds) const;
    void calculate_child_bounds(MAABBox *child_bounds) const;

private:
    MAABBox m_bounds;
    MOcTreeNode *m_children[8] = { nullptr };
    std::vector<MOcTreeItem *> m_items;
};

}

#endif
