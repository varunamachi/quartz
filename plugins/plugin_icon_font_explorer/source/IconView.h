#pragma once

#include <memory>

#include <QWidget>

namespace Quartz { namespace Ext { namespace IconFontExplorer {

class IconView : public QWidget {
    Q_OBJECT
public:
    IconView(QWidget* parent = nullptr);

    ~IconView();

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}}} // namespace Quartz::Ext::IconFontExplorer
