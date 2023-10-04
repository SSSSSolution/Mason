#ifndef MASON_CORE_IEVENT_DISPATCHER_H
#define MASON_CORE_IEVENT_DISPATCHER_H

#include <memory>

#include "core/MEvent.h"

#include "win-export/WinExport.h"

namespace mason {

class MASON_CORE_API IEventDispatcher {
public:
    IEventDispatcher() = default;
    virtual ~IEventDispatcher() = default;

    virtual void dispatch_event(std::shared_ptr<MEvent> event) = 0;
};

}

#endif
