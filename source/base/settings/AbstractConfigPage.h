#pragma once

#include <memory>

#include <QWidget>

#include "../QuartzBase.h"

namespace Quartz {

class QUARTZ_BASE_API AbstractConfigPage : public QWidget
{
    Q_OBJECT

public:
    AbstractConfigPage( const QString &id,
                        const QString &name,
                        const QStringList &parentPath,
                        const QIcon &icon,
                        QWidget *parent = nullptr );

    ~AbstractConfigPage();

    const QString & configPageId() const;

    const QString & configPageName() const;

    const QStringList & parentPath() const;

    const QIcon & icon() const;

    virtual bool apply() = 0;

    virtual bool setDefaults() = 0;

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};



}
