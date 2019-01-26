#pragma once

#include <memory>

#include <QWidget>

#include "../QuartzBase.h"

namespace Quartz {

class QUARTZ_BASE_API EditorManager : public QWidget
{
    Q_OBJECT

public:
    EditorManager(QWidget *parent);

    ~EditorManager() override;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}
