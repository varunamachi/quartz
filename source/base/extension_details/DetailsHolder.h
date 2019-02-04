#pragma once

#include "../QuartzBase.h"

#include <QWidget>

namespace Quartz { namespace Ext {

class QUARTZ_BASE_API DetailsHolder : public QWidget
{
public:
    DetailsHolder(QWidget *parent = nullptr);

    ~DetailsHolder();

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

} }
