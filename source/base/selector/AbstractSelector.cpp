#include <QIcon>

#include "AbstractSelector.h"

namespace Quartz {

struct AbstractSelector::Data {
    Data(const QString& id,
         const QString& name,
         const QIcon& icon,
         const QIcon& activeIcon)
        : m_id(id)
        , m_name(name)
        , m_icon(icon)
        , m_activeIcon(activeIcon) {
    }

    QString m_id;

    QString m_name;

    QIcon m_icon;

    QIcon m_activeIcon;
};

AbstractSelector::AbstractSelector(const QString& id,
                                   const QString& name,
                                   const QIcon& icon,
                                   const QIcon& activeIcon,
                                   QWidget* parent)
    : QWidget(parent)
    , m_data(std::make_unique<AbstractSelector::Data>(id,
                                                      name,
                                                      icon,
                                                      activeIcon)) {
}

AbstractSelector::~AbstractSelector() {
}

const QString& AbstractSelector::selectorId() const {
    return m_data->m_id;
}

const QString& AbstractSelector::selectorName() const {
    return m_data->m_name;
}

const QIcon& AbstractSelector::icon() const {
    return m_data->m_icon;
}

const QIcon& AbstractSelector::activeIcon() const {
    return m_data->m_activeIcon;
}

} // namespace Quartz
