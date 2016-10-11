#pragma once

#include <memory>

#include <QWidget>

namespace Quartz {

class AbstractSelector : public QWidget
{
    Q_OBJECT
public:
    AbstractSelector( const QString &selectorId,
                      const QString &selectorName,
                      QWidget *parent = nullptr );

    ~AbstractSelector();

    const QString & selectorId() const;

    const QString & selectorName() const;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
