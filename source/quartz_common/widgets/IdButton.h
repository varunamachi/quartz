#pragma once

#include <QPushButton>

namespace Vam { namespace Quartz {


class IdButton : public QPushButton
{
    Q_OBJECT
public:
    IdButton( QString id,
              QString text,
              int height,
              int width,
              QWidget *parent = 0 );

protected:
    void mouseReleaseEvent( QMouseEvent *evt );

signals:
    void activated( QString id );

private:
    QString m_id;
};
} }
