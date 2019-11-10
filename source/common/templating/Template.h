#pragma once

#include <memory>

#include <QString>

#include "../QuartzCommon.h"
#include "../model_view/TreeNode.h"

namespace Quartz {

class Config;

struct Content {
    Content()
        : m_name(QStringLiteral(""))
        , m_text(QStringLiteral(""))

    {
    }

    Content(const QString& name, const QString& text)
        : m_name(name)
        , m_text(text) {
    }

    QString m_name;

    QString m_text;
};

class QUARTZ_COMMON_API Template : public TreeNode {
public:
    explicit Template(const QString& name);

    ~Template() override;

    QString name() const;

    void setConfig(std::unique_ptr<Config> config);

    Config* config() const;

    void addContent(const Content& content);

    const Content& contentAt(int index) const;

    const QVector<Content>& contents() const;

    int numContents() const;

    QVariant fieldValue(int field) const override;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

} // namespace Quartz
