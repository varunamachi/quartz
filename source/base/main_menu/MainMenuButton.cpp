
#include <QMenu>
#include <QApplication>

#include <core/logger/Logging.h>

#include <common/iconstore/IconFontStore.h>

#include "MainMenuButton.h"
#include "AbstractMenuProvider.h"

namespace Quartz {

const QString MainMenuButton::ADAPTER_NAME("qz.main_menu");

struct MainMenuButton::Data {
    explicit Data(QWidget *parent)
        : m_menu(new QMenu(parent))
    {

    }

    QMenu *m_menu;

    QVector<QAction *> m_extActions;
};

MainMenuButton::MainMenuButton(QWidget *parent)
    : QToolButton(parent)
    , m_data(std::make_unique<Data>(this))
{
    this->setIcon(getActiveIcon(MatIcon::Menu));
    this->setMenu(m_data->m_menu);
    this->setPopupMode(QToolButton::InstantPopup);
    this->setArrowType(Qt::NoArrow);
    this->setObjectName("menu_button");
//    this->setText(tr("MENU"));
//    this->setStyleSheet("QToolButton#menu_button{background: transperant}");

    auto bgColor = QApplication::palette().color(QPalette::Text);
//    bgColor.setAlpha(100);
    QString qss;
    QTextStream qssStream;
    qssStream.setString(&qss);
    qssStream << "QToolButton#menu_button {"
                     "background-color: " << bgColor.name(QColor::HexArgb) <<
                 ";}"
                 "QToolButton#menu_button:menu-indicator{"
                    "width: 0px;"
                 "}";
    qssStream.flush();
    this->setStyleSheet(qss);
    this->setContentsMargins({});
}

MainMenuButton::~MainMenuButton()
{

}

void MainMenuButton::addAction(QAction *action)
{
    m_data->m_menu->addAction(action);
}

QAction * MainMenuButton::addMenu(QMenu *menu)
{
    return m_data->m_menu->addMenu(menu);
}

const QString &MainMenuButton::extensionType() const
{
    return  AbstractMenuProvider::EXTENSION_TYPE;
}

const QString &MainMenuButton::extensionAdapterName() const
{
    return ADAPTER_NAME;
}

bool MainMenuButton::handleExtension(Ext::Extension *extension)
{
    auto menuProvider = dynamic_cast<AbstractMenuProvider *>(extension);
    if (menuProvider != nullptr) {
        for (auto actn : menuProvider->actions()) {
            addAction(actn);
            m_data->m_extActions.push_back(actn);
        }
        for (auto menu : menuProvider->menus()) {
            auto menuAction = addMenu(menu);
            m_data->m_extActions.push_back(menuAction);
        }
        return true;
    } else {
        QZ_ERROR("Qz:Menu") << "Invalid extension provider";
    }
    return false;
}

bool MainMenuButton::finalizeExtension()
{
    for (auto o: m_data->m_extActions) {
        m_data->m_menu->removeAction(o);
        delete  o;
    }
    return true;
}



}

