

#include <QVBoxLayout>

#include <quartz_common/widgets/QzScroller.h>

#include "QuartzWindow.h"

namespace Vam { namespace Quartz {

QuartzWindow::QuartzWindow( QWidget *parent )
    : QMainWindow( parent )
{
    QWidget * widget = new QWidget( this );
    QVBoxLayout *layout = new QVBoxLayout();

    widget->setContentsMargins( QMargins() );
    layout->setContentsMargins( QMargins() );

    QzScroller *scroller = new QzScroller( Qt::Horizontal, this );
    layout->addWidget( scroller );

    widget->setLayout( layout );
    setCentralWidget( widget );
}


QString QuartzWindow::createStylesheet()
{
    return "QWidget{"
            "background-color: black; "
            "color: #FFA858;"
            "border-color: black;"
        "}"
        "QPushButton{"
            "background-color: #202020; "
            "color: #FFA858;"
            "border-width: 8px;"
            "border-color: black;"
        "}"
        "QPushButton:pressed{"
           "background-color: #FFA858; "
           "color: white;"
           "border-width: 8px;"
           "border-color: black;"
        "}"
        "QLabel{"
           "color: #FFA858; "
           "border-width: 8px;"
           "border-color: black;"
           "font: monospace;"
        "}"
        "QPushButton:checked{"
           "background-color: #FFA858; "
           "color: black;"
           "border-width: 8px;"
           "border-color: black;"
        "}"
        "QToolButton{"
            "background-color: #323232; "
            "color: #FFA858;"
            "border-style: outset;"
            "border-color: black;"
            "border-radius: 5px;"
            "min-width: 40px;"
            "min-height: 20px;"
            "font-size: 10px;"
        "}"
         "QToolButton:hover{"
             "background-color: #6F5C44;"
         "}"
         "QToolButton:pressed{"
           "background-color: #FFA858; "
           "color: #323232;"
        "}"
         "QToolButton:disabled{"
            "background-color: #404040; "
            "color: gray;"
        "}"
        "QToolBar{"
            "spacing: 3px;"
        "}"
        "QTreeView{ "
            "background-color: #151515;"
            "alternate-background-color: #202020;"
        "}"
        "QTreeView::item:selected:active, QTreeView::item:selected:!active,"
        "QListView::item:selected:active, QListView::item:selected:!active{"
            "color: #151515; "
              "background-color: rgba( 255, 168, 48, 200 );"
            "background-color: #B2936C;"
        "}"
        "QHeaderView::section {"
            "background-color: #202020;"
            "color: white;"
        "}"
        "QTreeView::item:hover, QListView::item:hover { "
            "background-color: rgba( 255, 168, 48, 50 );"
        "}"
        "QProgressBar{ "
            "border-radius: 5px;"
            "color: white;"
            "text-align: center;"
        "}"
        "QProgressBar::chunk {"
            "background-color: #FFA858;"
        "}"
        "QLineEdit{ background-color: #444444;}"
        "QMenu{ background-color: #444444;}"
        "QMenu::item:selected{background-color: #696969; }"
        "QScrollBar::handle {"
            "background: #6F5C44;;"
            "min-width: 30px;"
            "border-radius: 3px;"
        "}"
        "QScrollBar{"
            "background: #202020;"
            "border-radius: 5px;"
        "}"
        "QScrollBar::add-line, QScrollBar::sub-line{"
            "border: 2px solid #202020;"
            "background: #202020;"
        "}";
}


} }
