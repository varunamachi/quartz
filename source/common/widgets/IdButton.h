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
              QWidget *parent = 0,
              Qt::Orientation orientation = Qt::Horizontal );


protected:
    void mouseReleaseEvent( QMouseEvent *evt ) override;

    QSize originalSizeHint() const override;

signals:
    void activated( QString id );

private:
    QString m_id;

    QSize m_dim;
};
}
