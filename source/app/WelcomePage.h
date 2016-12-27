#pragma once

#include <QVBoxLayout>
#include <QLabel>

#include <base/content_manager/ContentWidget.h>

namespace Quartz {

class WelcomePage : public ContentWidget
{
    Q_OBJECT
public:
    explicit WelcomePage(
            const QString &id,
            QWidget *parent = nullptr )
        : ContentWidget( id,
                         tr( "Quartz" ),
                         "page",
                         parent )
    {
        QVBoxLayout *layout = new QVBoxLayout();
        QLabel *label = new QLabel( tr( "Welcome to Qurtz" ));
        layout->addWidget( label );
        this->setLayout( layout );
    }

    virtual ~WelcomePage() {}

private:

};

}
