#pragma once

#include <memory>

#include <QVariantHash>

#include <core/utils/Macros.h>

#include "../QuartzBase.h"

class QString;
class QColor;
class QPalette;
class QImage;
class QGradient;

namespace Quartz {

class QUARTZ_BASE_API Theme {
public:
    Theme(const QString& name);

    ~Theme();

    QString name() const;

    void setApplicationCSS(const QString& appCss);

    const QString& applicationCSS() const;

    void setColorPalette(const QPalette& palette);

    const QPalette& colorPalette() const;

    void setGradient(const QString& name, const QGradient& gradient);

    QGradient gradient(const QString& name);

    void setColor(const QString& name, const QColor& color);

    QColor color(const QString& name);

    void setImage(const QString& key, const QImage& image);

    const QVariantHash& declarations() const;

    void addDeclaration(const QString& key, const QVariant& value);

    const QImage& image(const QString& key) const;

    const QImage& image(const QString& key,
                        QZ_IN_OUT const QImage& defaultImage) const;

    void setCss(const QString& key, const QString& css);

    const QString& css(const QString& key) const;

    const QString& css(const QString& key,
                       QZ_IN_OUT const QString& defaultImage) const;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

} // namespace Quartz
