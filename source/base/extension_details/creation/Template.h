#pragma once

#include <memory>

#include <QString>

namespace Quartz {

class Template
{
public:
    explicit Template( const QString &name,
                       const QString &content );

    ~Template();

    QString name() const;

    void addVariable( const QString &key, const QString &value );

    QString variable( const QString &key ) const;

    const QString & content() const;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
