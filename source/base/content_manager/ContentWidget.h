#pragma once

#include <memory>

#include <QWidget>

#include "../QuartzBase.h"

namespace Quartz {

class QUARTZ_BASE_API ContentWidget : public QWidget
{
    Q_OBJECT
public:
    ContentWidget( const QString &id,
                   const QString &name,
                   const QString &kind,
                   QWidget *parent = nullptr );

    ~ContentWidget();

    const QString & id() const;

    const QString & name() const;

    const QString & kind() const;

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};


}
