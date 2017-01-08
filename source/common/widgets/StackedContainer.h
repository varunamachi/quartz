#pragma once

#include <memory>

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMouseEvent>

#include "QzScroller.h"
#include "IdButton.h"

namespace Quartz {



class AbstractContainer : public QWidget
{
    Q_OBJECT
public:
    enum class SelectorPosition
    {
        Before,
        After
    };

    explicit AbstractContainer( int selectorDimention,
                               int buttonDimention,
                               SelectorPosition selectorPosition,
                               Qt::Orientation orientation,
                               Qt::Orientation btnOriantation,
                               QWidget *parent = nullptr );

    ~AbstractContainer();

public:
    QWidget * widget( const QString &id ) const;

    QWidget * selectedWidget() const;

    QString currentId() const;

    QList< QString > allIds() const;

    int numWidgets() const;

    bool isEmpty();

    QStackedWidget * stackedWidget() const;

    QzScroller * selector() const;

    SelectorPosition selectorPosition() const;

    Qt::Orientation containerOrientation() const;

    Qt::Orientation buttonOrientation() const;

    int buttonWidth() const;

    int buttonHeight() const;

    virtual QString containerType() const = 0;

public Q_SLOTS:
    void addWidget( const QString &id,
                    const QString &displayName,
                    QWidget *widget );

    void removeWidget( const QString &id );

    void removeWidget( QWidget *widget );

    void select( const QString &id );

Q_SIGNALS:
    void sigSelected( const QString &id, QWidget *widget );

    void sigAdded( const QString &id, QWidget *widget );

    void sigRemoved( const QString &id );


private slots:
    void updateIndeces();

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};


class StackedContainer : public AbstractContainer
{
public:

    explicit StackedContainer( int selectorDimention,
                               int buttonDimention,
                               SelectorPosition selectorPosition,
                               Qt::Orientation orientation,
                               Qt::Orientation btnOriantation,
                               QWidget *parent = nullptr );

    ~StackedContainer();

    QString containerType() const override;
};


}

