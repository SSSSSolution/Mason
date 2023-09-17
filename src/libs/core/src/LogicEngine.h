#include "core/ILogicEngine.h"

namespace mason {

class LogicEngine : public ILogicEngine {
public:
    virtual void initialize() override;

    virtual void deinitialize() override;

    virtual void start() override;

    virtual void pause() override;

    virtual void stop() override;
};

}
