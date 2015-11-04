#pragma once

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "QzScroller.h"

namespace Vam { namespace Quartz {

class IdButton : public QPushButton
{
    Q_OBJECT
public:
    IdButton( QString id,
              QString text,
              QWidget *parent = 0 )
        : QPushButton( parent )
        , m_id( id )
    {
        setCheckable( true );
        setStyleSheet(
                    " QPushButton {"
                    "     border-radius: 5px;"
                    "     background-color: regba( 32, 32, 32, 200 );"
                    "     min-width: 60px;"
                    "     min-height: 60px;"
                    "     font-size: 10px;"
                    " }"
                    " QPushButton:checked {"
                    "     background-color: #FFA858;"
                    "     color: #202020;"
                    " }"
                    );
        setText( text );
    }

protected:
    void mousePressEvent( QMouseEvent *evt )
    {
        if( ! isChecked() ) {
            QPushButton::mousePressEvent( evt );
            emit activated( m_id );
        }
        evt->ignore();
    }

signals:
    void activated( QString id );

private:
    int m_id;
};



class StackedContainer : public QWidget
{
    Q_OBJECT
public:
    explicit StackedContainer( int selectorDimention,
                               Qt::Orientation orientation,
                               QWidget *parent = nullptr );

public:
    QWidget * widget( const QString &id ) const;

    QString currentId() const;

    QList< QString > allIds() const;

public slots:
    void addWidget( QString id, QWidget *widget );

    void removeWidget( QString id );

    void removeWidget( QWidget widget );

    void select( QString id );

signals:
    void sigSelected( QString &id );

    void sigAdded( QString &id, QWidget *widget );

private slots:
    void onSelected( QString &id );

private:
    QzScroller *m_selector;

    QStackedWidget *m_stackWidget;

    QString m_selectedId;

    QHash< QString, IdButton *> m_buttons;

    QHash< QString, QWidget *> m_widgets;
};


} }

