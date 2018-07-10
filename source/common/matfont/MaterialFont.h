#pragma once
//Adaped from QtAwesome - MIT Licensed



#include <memory>

#include <QHash>
#include <QIcon>

#include "../QuartzCommon.h"
#include "MatIcon.h"

class QString;
class QVariant;
class QIcon;
class QFont;
class QPainter;
class QRect;
class QFile;

namespace Quartz {

struct IMaterialFontPainter;

class QUARTZ_COMMON_API MaterialFont
{
public:

    explicit MaterialFont();

    virtual ~MaterialFont();

    void setDefaultOption( const QString& name, const QVariant& value  );

    QIcon icon(MatIcon character, const QVariantMap& options );

    QIcon icon(MatIcon character, int size, QColor color);

//    QIcon icon(MatIcon character);

    QFont font(int size);

    void give(const QString& name, IMaterialFontPainter* painter);

    QColor getColor(QIcon::Mode mode, QIcon::State state, QVariantMap opts);

    static bool init(const QByteArray &fontData);

    static MaterialFont * instance();

private:
    struct Data;
    std::unique_ptr< Data > m_data;

    static std::unique_ptr< MaterialFont > s_instance;

};


struct IMaterialFontPainter
{
    virtual void paint(MaterialFont* awesome,
                       QPainter* painter,
                       const QRect& rect,
                       QIcon::Mode mode,
                       QIcon::State state,
                       const QVariantMap& options ) = 0;

    virtual ~IMaterialFontPainter() {}
};

inline QIcon matIcon(MatIcon code, int size = -1, QColor color = QColor{}) {
    return MaterialFont::instance()->icon(code, size, color);
}

inline QIcon matIcon(MatIcon code, QVariantMap &opts) {
    return MaterialFont::instance()->icon(code, opts);
}

}

Q_DECLARE_METATYPE(Quartz::IMaterialFontPainter*)
