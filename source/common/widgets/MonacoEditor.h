#pragma once

#include <memory>

#include <QWidget>

#include "../QuartzCommon.h"

namespace Quartz {

class QUARTZ_COMMON_API MonacoEditor : public QWidget
{
    Q_OBJECT
public:
    explicit MonacoEditor(QWidget *parent = nullptr);

    ~MonacoEditor();

signals:

public slots:

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}
