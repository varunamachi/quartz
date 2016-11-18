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



class StackedContainer : public QWidget
{
    Q_OBJECT
public:
    enum class SelectorPosition
    {
        Before,
        After
    };

    explicit StackedContainer( int selectorDimention,
                               int buttonDimention,
                               SelectorPosition selectorPosition,
                               Qt::Orientation orientation,
                               Qt::Orientation btnOriantation,
                               QWidget *parent = nullptr );

public:
    QWidget * widget( const QString &id ) const;

    QString currentId() const;

    QList< QString > allIds() const;

    int numWidgets() const;

    bool isEmpty();

public slots:
    void addWidget( const QString &id,
                    const QString &displayName,
                    QWidget *widget );

    void removeWidget( const QString &id );

    void removeWidget( QWidget *widget );

    void select( const QString &id );

signals:
    void sigSelected( const QString &id );

    void sigAdded( const QString &id, QWidget *widget );

private slots:
    void updateIndeces();

private:
    struct Item {
        using Ptr = std::shared_ptr< Item >;

        IdButton *m_btn;

        QWidget *m_widget;

        int m_index;

        inline Item( int index, IdButton *btn, QWidget *widget )
            : m_index( index )
            , m_btn( btn )
            , m_widget( widget )
        {

        }

        static inline Item::Ptr create( int index,
                                        IdButton *btn,
                                        QWidget *widget )
        {
            return std::make_shared< Item >( index, btn, widget );
        }
    };

    int m_btnHeight;

    int m_btnWidth;

    Qt::Orientation m_btnOrientation;

    QzScroller *m_selector;

    QStackedWidget *m_stackWidget;

    QString m_selectedId;

    QHash< QString, Item::Ptr > m_items;
};


}

