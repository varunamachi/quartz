#pragma once

#include <memory>

#include <QWidget>

#include "../QuartzBase.h"

namespace Quartz {

class QzAppContext;

class QUARTZ_BASE_API AbstractSelector : public QWidget
{
    Q_OBJECT
public:
    AbstractSelector( const QString &selectorId,
                      const QString &selectorName,
                      const QIcon &icon,
                      QWidget *parent = nullptr );

    virtual ~AbstractSelector();

    const QString & selectorId() const;

    const QString & selectorName() const;

    const QIcon & icon() const;

    virtual void selected() = 0;

    virtual void unselected() = 0;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
