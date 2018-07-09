#pragma once

#include "OrientationButton.h"

namespace Quartz {


class IdButton : public OrientationButton
{
    Q_OBJECT
public:
    IdButton( QString id,
              QString text,
              int height,
              int width,
              QWidget *parent = nullptr,
              Qt::Orientation orientation = Qt::Horizontal );

    IdButton( QString id,
              QString text,
              int height,
              int width,
              const QIcon &icon,
              QWidget *parent = nullptr,
              Qt::Orientation orientation = Qt::Horizontal );

protected:
    void mouseReleaseEvent( QMouseEvent *evt ) override;

    QSize originalSizeHint() const override;

signals:
    void activated( QString id );

private:
    void setStyle(int width, int height);

    QString m_id;

    QSize m_dim;
};
}
