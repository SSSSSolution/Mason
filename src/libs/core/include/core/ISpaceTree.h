#ifndef MASON_CORE_ISPACE_TREE_H
#define MASON_CORE_ISPACE_TREE_H

#include "win-export/WinExport.h"

namespace mason {

class ISpaceItem {

};

class MASON_CORE_API ISpaceTree {
public:
    virtual void insert(ISpaceItem *item);
    virtual void remove(ISpaceItem *item);
};

}

#endif
