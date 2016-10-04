#pragma once

#include <QVBoxLayout>
#include <QLabel>

#include <base/page_manager/QuartzPage.h>

namespace Quartz {

class WelcomePage : public QuartzPage
{
    Q_OBJECT
public:
    explicit WelcomePage( QWidget *parent = nullptr )
        : QuartzPage( "qz_welcome",
                      tr( "Quartz" ),
                      tr( "Quartz" ),
                      tr( "Welcome" ),
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

class AnotherPage : public QuartzPage
{
    Q_OBJECT
public:
    explicit AnotherPage( QWidget *parent = nullptr )
        : QuartzPage( "qz_another",
                      tr( "Quartz" ),
                      tr( "Quartz" ),
                      tr( "AnotherPage" ),
                      parent )
    {
        QVBoxLayout *layout = new QVBoxLayout();
        QLabel *label = new QLabel( tr( "This is Q U A R T Z" ));
        layout->addWidget( label );
        this->setLayout( layout );
    }

    virtual ~AnotherPage() { }

private:

};

}
