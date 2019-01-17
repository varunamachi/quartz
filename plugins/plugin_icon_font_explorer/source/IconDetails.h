#pragma once

#include <memory>

#include <QWidget>

namespace Quartz { namespace Ext { namespace IconFontExplorer {

class IconDetails : public QWidget
{
    Q_OBJECT
public:
    IconDetails(QWidget *parent = nullptr);

    ~IconDetails();

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

} } }
