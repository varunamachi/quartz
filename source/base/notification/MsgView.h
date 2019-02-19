#pragma once

#include <base/view_manager/QuartzView.h>

#include "../QuartzBase.h"

namespace Quartz {

class Msg;

class QUARTZ_BASE_API MsgView : public QuartzView
{
    Q_OBJECT

public:
    MsgView(QWidget *parent);

    ~MsgView() override;

    void addMessage(std::shared_ptr<Msg> msg);

    static const QString VIEW_ID;

    static const QString VIEW_DISPLAY_NAME;

    static const QString VIEW_CATEGORY;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}
