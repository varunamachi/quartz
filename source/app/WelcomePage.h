#pragma once

#include <QVBoxLayout>
#include <QLabel>

#include <quartz_core/IQuartzPageManager.h>

namespace Vam { namespace Quartz {

class WelcomePage : public QuartzPage
{
    Q_OBJECT
public:
    explicit WelcomePage( QWidget *parent = nullptr )
        : QuartzPage( "qz_welcome",
                      tr( "Quartz" ),
                      tr( "Quartz" ),
                      tr("Welcome"),
                      parent )
    {
        QVBoxLayout *layout = new QVBoxLayout();
        QLabel *label = new QLabel( tr( "Welcome to Qurtz" ));
        layout->addWidget( label );
        this->setLayout( layout );
    }

private:

};

} }
