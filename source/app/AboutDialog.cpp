#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>

#include "AboutDialog.h"

namespace Quartz {

AboutDialog::AboutDialog(QWidget *parent)
{
    auto layout = new QHBoxLayout();
    auto img = new QLabel(this);
    img->setPixmap(QPixmap("://resources/quartz32.png"));
//    img->setMaximumSize()
    auto desc = new QLabel(this);
    desc->setText(tr("This is quartz!"));
    layout->addWidget(img);
    layout->addWidget(desc);
    this->setLayout(layout);
    this->setMinimumSize({300, 100});
}

AboutDialog::~AboutDialog()
{

}


}
