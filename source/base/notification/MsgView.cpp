#include <QVector>
#include <QVBoxLayout>
#include <QHeaderView>

#include <common/iconstore/IconFontStore.h>
#include <common/model_view/ArrayModel.h>
#include <common/widgets/QzTreeView.h>

#include "Msg.h"
#include "MsgView.h"

namespace Quartz {

const QString MsgView::VIEW_ID{"qz.msg_view"};
const QString MsgView::VIEW_DISPLAY_NAME("Msg");
const QString MsgView::VIEW_CATEGORY{"qz.inbuilt"};

struct MsgView::Data {
    explicit Data(MsgView* parent)
        : m_model(new ArrayModel(3,
                                 false,
                                 true,
                                 {QStringLiteral("      Type       "),
                                  QStringLiteral("      Time       "),
                                  QStringLiteral("     Message     ")},
                                 parent))
        , m_view(new QzTreeView(parent)) {
        m_view->setModel(m_model);
        m_view->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }

    ArrayModel* m_model;

    QzTreeView* m_view;

    QVector<std::shared_ptr<Msg>> m_msgs;
};

MsgView::MsgView(QWidget* parent)
    : QuartzView(VIEW_ID,
                 VIEW_CATEGORY,
                 VIEW_DISPLAY_NAME,
                 getNormalIcon(MatIcon::Notifications),
                 getActiveIcon(MatIcon::Notifications),
                 parent)
    , m_data(std::make_unique<Data>(this)) {
    m_data->m_view->setRootIsDecorated(false);

    auto mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_data->m_view);
    this->setLayout(mainLayout);

    this->setContentsMargins({});
    mainLayout->setContentsMargins({});
}

MsgView::~MsgView() {
}

void MsgView::addMessage(std::shared_ptr<Msg> msg) {
    m_data->m_msgs.append(msg);
    m_data->m_model->addRoot(msg.get());
    m_data->m_view->scrollToBottom();
}

} // namespace Quartz
