#pragma once
//Adaped from QtAwesome - MIT Licensed



#include <memory>

#include <QHash>
#include <QIcon>

#include "../QuartzCommon.h"
#include "MatIcon.h"
#include "FAIcon.h"

class QString;
class QVariant;
class QIcon;
class QFont;
class QPainter;
class QRect;
class QFile;

namespace Quartz {

struct IIconFontPainter;

class QUARTZ_COMMON_API IconFontStore
{
public:
    explicit IconFontStore();

    virtual ~IconFontStore();

    void setDefaultOption( const QString& name, const QVariant& value  );

    QIcon icon(const QString &fontName,
               int character,
               const QVariantMap &options );

    QIcon icon(const QString &fontName,
               int character,
               int size,
               QColor color);

    QFont font(const QString &fontName, int size);

    void give(const QString& name, IIconFontPainter* painter);

    QColor getColor(QIcon::Mode mode, QIcon::State state, QVariantMap opts);

    QColor getColor(QIcon::Mode mode);

    static bool init(const QByteArrayList &fontData);

    static IconFontStore * instance();

    static const QString FONT_MATERIAL;

    static const QString FONT_FA_BRANDS;

    static const QString FONT_FA_SOLID;

private:
    struct Data;
    std::unique_ptr< Data > m_data;

    static std::unique_ptr< IconFontStore > s_instance;
};




struct IIconFontPainter
{
    virtual void paint(IconFontStore* awesome,
                       QPainter* painter,
                       const QRect& rect,
                       QIcon::Mode mode,
                       QIcon::State state,
                       const QVariantMap& options ) = 0;

    virtual ~IIconFontPainter() {}
};


inline QIcon getIcon(MatIcon code, int size = -1, QColor color = QColor{}) {
    return IconFontStore::instance()->icon(
                IconFontStore::FONT_MATERIAL,
                static_cast<int>(code),
                size,
                color);
}

inline QIcon getIcon(MatIcon code, QVariantMap &opts) {
    return IconFontStore::instance()->icon(
                IconFontStore::FONT_MATERIAL,
                static_cast<int>(code),
                opts);
}
inline QIcon getIcon(FAIcon code, QVariantMap &opts) {
    return IconFontStore::instance()->icon(
                IconFontStore::FONT_FA_SOLID,
                static_cast<int>(code),
                opts);
}
inline QIcon getIcon(FAIcon code, int size = -1, QColor color = QColor{}) {
    return IconFontStore::instance()->icon(
                IconFontStore::FONT_FA_SOLID,
                static_cast<int>(code),
                size,
                color);
}
inline QIcon getIcon(FABrandIcon code, int size = -1, QColor color = QColor{}) {
    return IconFontStore::instance()->icon(
                IconFontStore::FONT_FA_BRANDS,
                static_cast<int>(code),
                size,
                color);
}
inline QIcon getIcon(FABrandIcon code, QVariantMap &opts) {
    return IconFontStore::instance()->icon(
                IconFontStore::FONT_FA_BRANDS,
                static_cast<int>(code),
                opts);
}

template<typename IconType>
inline QIcon getNormalIcon(IconType code) {
    return getIcon(code,
                   -1,
                   IconFontStore::instance()->getColor(QIcon::Normal));
}

template<typename IconType>
inline QIcon getActiveIcon(IconType code) {
    return getIcon(code,
                   -1,
                   IconFontStore::instance()->getColor(QIcon::Selected));
}

}

Q_DECLARE_METATYPE(Quartz::IIconFontPainter*)
