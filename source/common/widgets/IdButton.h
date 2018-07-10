#pragma once

#include <QToolButton>

namespace Quartz {


class IdButton : public QToolButton
{
    Q_OBJECT
public:
    IdButton( QString id,
              QString text,
              int height,
              int width,
              QWidget *parent = nullptr);

    IdButton( QString id,
              QString text,
              int height,
              int width,
              const QIcon &icon,
              bool textBelowIcon,
              QWidget *parent = nullptr);

protected:
    void mouseReleaseEvent( QMouseEvent *evt ) override;

//    QSize originalSizeHint() const override;
      QSize sizeHint() const override;

signals:
    void activated( QString id );

private:
    void setStyle(int width, int height, bool big);

    QString m_id;

    QSize m_dim;
};
}
