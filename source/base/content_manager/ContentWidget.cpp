#include <QApplication>

#include "ContentWidget.h"

namespace Quartz {

struct ContentWidget::Data
{
    Data(const QString &id,
          const QString &name,
          const QString &kind)
        : m_id(id)
        , m_name(name)
        , m_kind(kind)
    {

    }

    const QString m_id;

    const QString m_name;

    const QString m_kind;
};

ContentWidget::ContentWidget(const QString &id,
                              const QString &name,
                              const QString &kind,
                              QWidget *parent)
    : QWidget(parent)
//    , m_data(std::make_unique<Data>(id, name, kind))
    , m_data(std::make_unique<Data>(id, name, kind))
{
}

ContentWidget::~ContentWidget()
{

}

const QString & ContentWidget::id() const
{
    return m_data->m_id;
}

const QString & ContentWidget::name() const
{
    return m_data->m_name;
}

const QString & ContentWidget::kind() const
{
    return m_data->m_kind;
}

}
