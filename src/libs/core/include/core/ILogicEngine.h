#ifndef MASON_ILOGIC_ENGINE_H
#define MASON_ILOGIC_ENGINE_H

#include <memory>
#include <string>

namespace mason {

class ILogicEngine {
public:
    virtual void initialize() = 0;

    virtual void deinitialize() = 0;

    virtual void start() = 0;

    virtual void pause() = 0;

    virtual void stop() = 0;
};

class LogicEngineFactory {
public:
    static std::unique_ptr<ILogicEngine> create(const std::string &name);
};

}



#endif
