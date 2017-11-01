#pragma once

#include <memory>

#include <QWidget>

class QModelIndex;

namespace Quartz {

class TemplateManager;

namespace Plugin { namespace Creator {

/**
 * @brief The TemplateSelectorWidget class allows selecting template to be used
 * for generation
 */
class TemplateSelectorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TemplateSelectorWidget(
            TemplateManager *templateManager,
            QWidget *parent = nullptr );

    ~TemplateSelectorWidget();

    void selected( const QModelIndex &index );

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

} } }
