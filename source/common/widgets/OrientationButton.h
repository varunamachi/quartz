/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** orientationbutton.h
** This is an extended version of Qt's QPushButton. In addition to
** QPushButton's functionality, this button's orientation can be changed
** to vertical and the button can also be mirrored.
**
** Author:	J-P Nurmi
** Date:	23th September 2006
** -------------------------------------------------------------------------
**
** // Modified for Tanyatu by Varuna L Amachi, 2013 /////////////////////// */
#pragma once

#include <QPushButton>
#include <QStyleOptionButton>

#include "../QuartzCommon.h"

namespace Quartz {

class QUARTZ_COMMON_API OrientationButton : public QPushButton {
public:
    OrientationButton(QWidget* parent = 0);

    OrientationButton(const QString& text, QWidget* parent = 0);

    OrientationButton(const QIcon& icon,
                      const QString& text,
                      QWidget* parent = 0);

    ~OrientationButton();

    Qt::Orientation orientation() const;

    void setOrientation(Qt::Orientation orientation);

    bool mirrored() const;

    void setMirrored(bool mirrored);

    QSize sizeHint() const;

    QSize minimumSizeHint() const;

protected:
    void paintEvent(QPaintEvent* event);

    virtual QSize originalSizeHint() const;

private:
    QStyleOptionButton getStyleOption() const;

    void init();

    Qt::Orientation m_orientation;

    bool m_mirrored;
};

} // namespace Quartz
