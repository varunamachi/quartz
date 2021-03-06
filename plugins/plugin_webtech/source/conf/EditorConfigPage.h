#pragma once

#include <memory>

#include <QWidget>

namespace Quartz { namespace Ext { namespace WebTech {

class EditorConfigPage : public QWidget {
    Q_OBJECT
public:
    EditorConfigPage(QWidget* parent = nullptr);

    ~EditorConfigPage() override;

    void refresh();

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}}} // namespace Quartz::Ext::WebTech
