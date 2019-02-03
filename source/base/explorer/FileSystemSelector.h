#pragma once

#include <memory>

#include "../QuartzBase.h"
#include "../selector/AbstractSelector.h"

namespace Quartz {

class QUARTZ_BASE_API FileSystemSelector : public AbstractSelector
{
    Q_OBJECT

public:
    FileSystemSelector(QWidget *parent);

    ~FileSystemSelector() override;

    void selected() override;

    void unselected() override;

    static const QString SELECTOR_ID;
    static const QString SELECTOR_NAME;
    static const QString CONFIG_PATH;
    static const QString CONFIG_RECENT_PATHS;

public Q_SLOTS:
    QString setPath(const QString &path);

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}
