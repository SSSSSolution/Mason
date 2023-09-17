#ifndef MASON_RENDER_ENGINE_H
#define MASON_RENDER_ENGINE_H

#include "core/IRenderEngine.h"

namespace mason {

class RenderEngine : public IRenderEngine {
public:
    virtual void initialize() override;
    virtual void deinitialize() override;

    virtual void start() override;
    virtual void pause() override;
    virtual void stop() override;
};

}

#endif
