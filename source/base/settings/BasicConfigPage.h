#pragma once

#include <memory>

#include "AbstractConfigPage.h"

class QString;
class QWidget;

namespace Quartz {

class BasicConfigPage : public AbstractConfigPage
{
    Q_OBJECT

public:
    BasicConfigPage( QWidget *parent = nullptr );

    ~BasicConfigPage();

    bool apply() override;

    bool setDefaults() override;

    static const QString CONFIG_PAGE_ID;

    static const QString CONFIG_PAGE_NAME;

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};


}
