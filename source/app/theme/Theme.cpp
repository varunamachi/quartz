
#include <QHash>

#include "Theme.h"

namespace Quartz {

struct Theme::Data
{
    explicit Data( const QString &name )
        : m_name( name )
    {

    }

    QString m_name;

    QHash< QString, QColor > m_colors;

    QHash< QString, QImage > m_images;

    QHash< QString, QBrush > m_brushs;

    QHash< QString, QPen > m_pens;

    QHash< QString, QString > m_styles;
};

Theme::Theme( const QString &name )
//    : m_data( std::make_unique< Theme::Data >( name )),
    : m_data( new Theme::Data( name ))
{

}

Theme::~Theme()
{

}

void Theme::setColor( const QString &key, const QColor &color )
{
    m_data->m_colors.insert( key, color );
}


void Theme::setImage( const QString &key, const QImage &image )
{
    m_data->m_images.insert( key, image );
}


void Theme::setPen( const QString &key, const QPen &pen )
{
    m_data->m_pens.insert( key, pen );
}


void Theme::setCss( const QString &key, const QString &css )
{
    m_data->m_styles.insert( key, css );
}


QString Theme::name() const
{
    return m_data->m_name;
}


const QColor Theme::color( const QString &key, QColor def ) const
{
    if( m_data->m_colors.contains( key )) {
        return m_data->m_colors.value( key );
    }
    return def;
}


const QImage Theme::image( const QString &key, QImage def ) const
{
    if( m_data->m_images.contains( key )) {
        return m_data->m_images.value( key );
    }
    return def;
}


const QBrush Theme::brush( const QString &key, QBrush def ) const
{
    if( m_data->m_brushs.contains( key )) {
        return m_data->m_brushs.value( key );
    }
    return def;
}


const QPen Theme::pen( const QString &key, QPen def ) const
{
    if( m_data->m_pens.contains( key )) {
        return m_data->m_pens.value( key );
    }
    return def;
}


const QString Theme::css( const QString &key, QString def ) const
{
    if( m_data->m_styles.contains( key )) {
        return m_data->m_styles.value( key );
    }
    return def;
}


}
