
#include <QIcon>

#include "QuartzView.h"

namespace  Quartz {

struct QuartzView::Data
{
public:
    Data(const QString &viewId,
          const QString &category,
          const QString &displayName,
          const QIcon &icon,
          const QIcon &activeIcon)
        : m_viewId(viewId)
        , m_categoryId(category)
        , m_displayName(displayName)
        , m_icon(icon)
        , m_activeIcon(activeIcon)
    {

    }

    QString m_viewId;

    QString m_categoryId;

    QString m_categoryName;

    QString m_displayName;

    QIcon m_icon;

    QIcon m_activeIcon;
};

QuartzView::QuartzView(const QString &viewId,
                       const QString &category,
                       const QString &displayName,
                       const QIcon &icon,
                       const QIcon &activeIcon,
                       QWidget *parent)
    : QWidget(parent)
    , m_data(std::make_unique<Data>(viewId,
                                    category,
                                    displayName,
                                    icon,
                                    activeIcon))
{

}

QuartzView::~QuartzView()
{

}

const QString & QuartzView::viewId() const
{
    return m_data->m_viewId;
}

const QString & QuartzView::viewCategoryId() const
{
    return m_data->m_categoryId;
}

const QString & QuartzView::viewDisplayName() const
{
    return m_data->m_displayName;
}

const QString & QuartzView::viewCategoryName() const
{
    return m_data->m_categoryName;
}

const QIcon &QuartzView::icon() const
{
    return m_data->m_icon;
}

const QIcon &QuartzView::activeIcon() const
{
    return m_data->m_activeIcon;
}

}
