#pragma once

#include <memory>

#include <QString>

namespace Quartz { namespace Plugin { namespace Creator {

class Variable;

class Template
{
public:
    explicit Template( const QString &name,
                       const QString &content );

    ~Template();

    QString name() const;

    void addVariable( const QString &key,
                      const QString &value,
                      const QString &description );

    const Variable & variable( const QString &key ) const;

    const Variable & variableAt( int index ) const;

    const QString & content() const;

    static const Variable EMPTY_VARIABLE;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

} } }
