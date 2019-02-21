
#include <QStringList>
#include <QMap>
#include <QVector>
#include <QVariant>

#include "../generic_config/model/Config.h"
#include "Template.h"
#include "TemplateInstance.h"

namespace Quartz {

struct Template::Data
{
    Data(const QString &name)
        : m_name(name)
    {

    }

    QString m_name;

    std::unique_ptr<Config> m_config;

    QVector<Content> m_contents;
};

const auto EMPTY_CONTENT = Content{"", ""};



Template::Template(const QString &name)
    : TreeNode(2, nullptr)
    , m_data(std::make_unique<Data>(name))
{

}

Template::~Template()
{

}

QString Template::name() const
{
    return m_data->m_name;
}

void Template::setConfig(std::unique_ptr<Config> config)
{
    m_data->m_config = std::move(config);
}

Config * Template::config() const
{
    return  m_data->m_config.get();
}

void Template::addContent(const Content &content)
{
    m_data->m_contents.append(content);
}

const Content &Template::contentAt(int index) const
{
    if (index < m_data->m_contents.size()) {
        return m_data->m_contents.at(index);
    }
    return EMPTY_CONTENT;
}

const QVector<Content> &Template::contents() const
{
    return m_data->m_contents;
}

int Template::numContents() const
{
    return m_data->m_contents.size();
}


QVariant Template::fieldValue(int column) const
{
    switch(column) {
    case 0: return m_data->m_name;
    case 1: return numChildren();
    }
    return QVariant{};
}

}
