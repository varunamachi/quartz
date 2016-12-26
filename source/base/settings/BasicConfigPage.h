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
    BasicConfigPage( const QString &id,
                     const QString &name,
                     QWidget *parent = nullptr );

    ~BasicConfigPage();

    bool apply() override;

    bool setDefaults() override;

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};


}
