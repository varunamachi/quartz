#pragma once

#include <memory>

#include <core/QzCoreContext.h>

#include "QuartzBase.h"



namespace Quartz {

class ContentManager;
class SelectorManager;
class GeneralSelector;
class PlugginManager;





class QUARTZ_BASE_API QzAppContext : public QzCoreContext
{
public:
    explicit QzAppContext();

    ~QzAppContext();


    QZCONTEXT_FUNC_DECL( ContentManager, contentManager );
    QZCONTEXT_FUNC_DECL( SelectorManager, selectorManager );
    QZCONTEXT_FUNC_DECL( GeneralSelector, nodeSelector );

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
