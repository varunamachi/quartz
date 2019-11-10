/**
 * Copyright 2014 mhcuervo
 * Based on code from stackoverflow:
 * http://stackoverflow.com/questions/23718827/qt-shadow-around-window
 *
 * As discussed here:
 * http://meta.stackexchange.com/questions/54766
 * /code-at-stackoverflow-under-any-license
 * This is covered under CC-BY-SA, it can be found at:
 * http://creativecommons.org/licenses/by-sa/4.0/
 *
 */

#pragma once

#include <QGraphicsEffect>

#include <QGraphicsDropShadowEffect>
#include <QGraphicsEffect>

class CustomShadowEffect : public QGraphicsEffect {
    Q_OBJECT
public:
    explicit CustomShadowEffect(QObject* parent = 0);

    void draw(QPainter* painter);

    QRectF boundingRectfor(const QRectF& rect) const;

    inline void setDistance(qreal distance) {
        _distance = distance;
        updateBoundingRect();
    }

    inline qreal distance() const {
        return _distance;
    }

    inline void setBlurRadius(qreal blurRadius) {
        _blurRadius = blurRadius;
        updateBoundingRect();
    }

    inline qreal blurRadius() const {
        return _blurRadius;
    }

    inline void setColor(const QColor& color) {
        _color = color;
    }

    inline QColor color() const {
        return _color;
    }

private:
    qreal _distance;

    qreal _blurRadius;

    QColor _color;
};
