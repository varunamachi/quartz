#pragma once

#include <memory>

#include <QWidget>

namespace Quartz {

struct IconInfo;

namespace Ext { namespace IconFontExplorer {

class IconDetails : public QWidget
{
    Q_OBJECT
public:
    IconDetails(QWidget *parent = nullptr);

    ~IconDetails();

public slots:
    void setIconInfo(const IconInfo *info);

    void update();

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

} } }
