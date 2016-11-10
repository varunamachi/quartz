#pragma once

#include <memory>

#include <QWidget>

#include "../QuartzBase.h"

namespace Quartz {

class Context;

class QUARTZ_BASE_API AbstractSelector : public QWidget
{
    Q_OBJECT
public:
    AbstractSelector( const Context *context,
                      const QString &selectorId,
                      const QString &selectorName,
                      QWidget *parent = nullptr );

    virtual ~AbstractSelector();

    const QString & selectorId() const;

    const QString & selectorName() const;

protected:
    const Context * context() const;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
