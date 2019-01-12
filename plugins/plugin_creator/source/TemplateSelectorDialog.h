#pragma once

#include <memory>

#include <QDialog>

class QModelIndex;

namespace Quartz {

class TemplateManager;
class Template;

namespace Ext { namespace Creator {

/**
 * @brief The TemplateSelectorWidget class allows selecting template to be used
 * for generation
 */
class TemplateSelectorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TemplateSelectorDialog(
            TemplateManager *templateManager,
            QWidget *parent = nullptr);

    ~TemplateSelectorDialog();

    QVector< Template * > selectedTemplates() const;

    void clearSelection();

private:
    struct Data;
    std::unique_ptr<Data> m_data;

};

} } }
