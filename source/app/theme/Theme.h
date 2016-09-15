#pragma once

#include <memory>

#include <QColor>
#include <QImage>
#include <QBrush>
#include <QPen>

class QString;

namespace Quartz {

class Theme
{
public:
    Theme( const QString &name,
           const QColor &defaultColor,
           const QImage &image,
           const QBrush &brush,
           const QPen &pen );

    ~Theme();

    void setColor( const QString &key,
                   const QColor &color );

    void setImage( const QString &key, const QImage &image );

    void setBrush( const QString &key, const QBrush &brush );

    void setPen( const QString &key, const QPen &Pen );

    void setCss( const QString &key, const QString &css );

    const QColor color( const QString &key, QColor def = QColor{} ) const;

    const QImage image( const QString &key, QImage def = QImage{} ) const;

    const QBrush brush( const QString &key, QBrush def = QBrush{} ) const;

    const QPen pen( const QString &key, QPen def = QPen{}) const;

    const QString css( const QString &key, QString def = QString{} ) const;

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

}
