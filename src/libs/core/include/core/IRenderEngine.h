#ifndef MASON_IRENDER_ENGINE_H
#define MASON_IRENDER_ENGINE_H

#include <string>
#include <memory>

namespace mason {
    class IRenderEngine {
    public:
        virtual void initialize() = 0;
        virtual void deinitialize() = 0;

        virtual void start() = 0;
        virtual void pause() = 0;
        virtual void stop() = 0;
    };

    class RenderEngineFactory {
    public:
        static std::unique_ptr<IRenderEngine> create(const std::string &name);
    };
}


#endif
