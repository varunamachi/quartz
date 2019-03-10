#include <QHash>
#include <QString>
#include <QPalette>
#include <QImage>
#include <QGradient>

#include "Theme.h"

namespace Quartz {

struct Theme::Data
{
    explicit Data(const QString &name)
        : m_name(name)
    {

    }

    QString m_name;

    QString m_appCss;

    QPalette m_palette;

    QHash<QString, QImage> m_images;

    QHash<QString, QColor> m_colors;

    QHash<QString, QGradient> m_gradients;

    QHash< QString, QString > m_css;

    static const QImage EMPTY_IMAGE;

    static const QString EMPTY_CSS;

};

const QImage Theme::Data::EMPTY_IMAGE{};
const QString Theme::Data::EMPTY_CSS{};

Theme::Theme(const QString &name)
//    : m_data(std::make_unique<Theme::Data>(name)),
    : m_data(new Theme::Data(name))
{

}

Theme::~Theme()
{

}

QString Theme::name() const
{
    return m_data->m_name;
}

void Theme::setApplicationCSS(const QString &appCss)
{
    m_data->m_appCss = appCss;
}

const QString & Theme::applicationCSS() const
{
    return m_data->m_appCss;
}

void Theme::setColorPalette(const QPalette &palette)
{
    m_data->m_palette = palette;
}

const QPalette & Theme::colorPalette() const
{
    return m_data->m_palette;
}

void Theme::setGradient(const QString &name, const QGradient &grad)
{
    m_data->m_gradients.insert(name, grad);
}

QGradient Theme::gradient(const QString &name)
{
    return m_data->m_gradients.value(name, QGradient{});
}

void Theme::setColor(const QString &name, const QColor &color)
{
    m_data->m_colors.insert(name, color);
}

QColor Theme::color(const QString &name)
{
    return m_data->m_colors.value(name, QColor{});
}

void Theme::setImage(const QString &key, const QImage &image)
{
    m_data->m_images[key] = image;
}

const QImage & Theme::image(const QString &key) const
{
    return image(key, Data::EMPTY_IMAGE);
}

const QImage & Theme::image(const QString &key,
                             QZ_IN_OUT const QImage &defaultImage) const
{
    if (m_data->m_images.contains(key)) {
        return m_data->m_images[ key ];
    }
    return defaultImage;
}

void Theme::setCss(const QString &key, const QString &css)
{
    m_data->m_css[ key ] = css;
}

const QString  & Theme::css(const QString &key) const
{
    return css(key, Data::EMPTY_CSS);
}

const QString  & Theme::css(const QString &key,
                             QZ_IN_OUT const QString &defaultCSS) const
{
    if (m_data->m_css.contains(key)) {
        return m_data->m_css[ key ];
    }
    return defaultCSS;
}

}
