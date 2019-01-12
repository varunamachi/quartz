#pragma once

#include <memory>

#include <base/title_bar/AbstractTitleItemProvider.h>
#include <base/title_bar/QuartzItem.h>

namespace Quartz { namespace Ext { namespace Sample {

class TitleBarButton : public QuartzItem
{
    Q_OBJECT
public:
    explicit TitleBarButton(QWidget *parent = nullptr);

    ~TitleBarButton();

    static const QString ITEM_ID;

    static const QString ITEM_CATERGORY;
};


class TitleItemProvider : public AbstractTitleItemProvider
{
public:
    TitleItemProvider();

    ~TitleItemProvider();

    bool init() override;

    bool destroy() override;

    QVector< QuartzItem *> titleItems() const override;

    static const QString     EXTENSION_ID;

    static const QString     EXTENSION_NAME;

private:

};

} } }
