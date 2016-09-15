
#include <QHash>

#include "Theme.h"

namespace Quartz {

struct Theme::Data
{
public:
    QHash< QString, QColor > m_color;

    QHash< QString, QImage > m_image;

    QHash< QString, QBrush > m_brush;
};

Theme::Theme( const QString &name,
              const QColor &defaultColor,
              const QImage &image,
              const QBrush &brush,
              const QPen &pen )
{

}

Theme::~Theme()
{

}

void Theme::setColor( const QString &key, const QColor &color )
{
}


void Theme::setImage( const QString &key, const QImage &image )
{
}


void Theme::setPen( const QString &key, const QPen &Pen )
{
}


void Theme::setCss( const QString &key, const QString &css )
{
}


const QColor Theme::color( const QString &key, QColor def ) const
{
    return def;
}


const QImage Theme::image( const QString &key, QImage def ) const
{
    return def;
}


const QBrush Theme::brush( const QString &key, QBrush def ) const
{
    return def;
}


const QPen Theme::pen( const QString &key, QPen def ) const
{
    return def;
}


const QString Theme::css( const QString &key, QString def ) const
{
    return def;
}


}
