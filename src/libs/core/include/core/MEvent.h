#ifndef MASON_CORE_MEVENT_H
#define MASON_CORE_MEVENT_H

#include "win-export/WinExport.h"

namespace mason {

class MASON_CORE_API MEvent {
public:
    enum Type {
        MAppStart = 0,
        MAppPause,
        MAppFinish,
    };

    MEvent(Type t) : m_type(t) {}
    virtual ~MEvent() = default;

    Type type() const { return m_type; }

private:
    Type m_type;
};

}

#endif
