

#include <QHash>

#include "Theme.h"
#include "ThemeManager.h"

namespace Quartz {

class ThemeManager::Impl {
public:
    explicit Impl(std::shared_ptr<Theme> defaultTheme)
        : m_defaultTheme(defaultTheme) {
    }

    std::shared_ptr<Theme> defaultTheme() const {
        return m_defaultTheme;
    }

    std::shared_ptr<Theme> theme(const QString& name) const {
        auto theme = m_themes.value(name);
        return theme;
    }

    void addTheme(std::shared_ptr<Theme> theme) {
        if (theme) {
            m_themes.insert(theme->name(), theme);
        }
    }

    const std::shared_ptr<Theme> current() const {
        auto theme = m_themes.value(m_selected);
        if (!theme) {
            return m_defaultTheme;
        }
        return theme;
    }

    void selectTheme(const QString& themeName) {
        if (m_themes.contains(themeName)) {
            m_selected = themeName;
        }
    }

private:
    QHash<QString, std::shared_ptr<Theme>> m_themes;

    QString m_selected;

    std::shared_ptr<Theme> m_defaultTheme;
};

ThemeManager::ThemeManager(std::shared_ptr<Theme> defaultTheme)
    //    : m_impl(std::make_unique<Impl>(defaultTheme))
    : m_impl(new Impl(defaultTheme))

{
}

ThemeManager::~ThemeManager() {
}

std::shared_ptr<Theme> ThemeManager::defaultTheme() const {
    return m_impl->defaultTheme();
}

std::shared_ptr<Theme> ThemeManager::theme(const QString& name) const {
    return m_impl->theme(name);
}

void ThemeManager::addTheme(std::shared_ptr<Theme> theme) {
    m_impl->addTheme(theme);
}

const std::shared_ptr<Theme> ThemeManager::current() const {
    return m_impl->current();
}

void ThemeManager::selectTheme(const QString& themeName) {
    m_impl->selectTheme(themeName);
}

} // namespace Quartz
