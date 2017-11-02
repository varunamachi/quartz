#pragma once

#include <memory>

#include <QDialog>

class QModelIndex;

namespace Quartz {

class TemplateManager;
class Template;

namespace Plugin { namespace Creator {

/**
 * @brief The TemplateSelectorWidget class allows selecting template to be used
 * for generation
 */
class TemplateSelectorWidget : public QDialog
{
    Q_OBJECT
public:
    explicit TemplateSelectorWidget(
            TemplateManager *templateManager,
            QWidget *parent = nullptr );

    ~TemplateSelectorWidget();

//    void selected( const QModelIndex &index );

    QVector< Template * > getSelected() const;

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

} } }
