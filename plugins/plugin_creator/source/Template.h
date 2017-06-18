#pragma once

#include <memory>

#include <QString>

namespace Quartz {


class Template
{
public:
    struct Variable
    {
        QString m_name;

        QString m_value;

        QString m_description;
    };

    explicit Template( const QString &name,
                       const QString &content );

    ~Template();

    QString name() const;

    void addVariable( const QString &key,
                      const QString &value,
                      const QString &description );

    const Variable variable( const QString &key ) const;

    const QString & content() const;

    static const Variable EMPTY_VARIABLE;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
