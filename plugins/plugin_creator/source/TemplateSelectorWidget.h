#pragma once

#include <memory>

#include <QWidget>

namespace Quartz {

namespace Plugin { namespace Creator {

class TemplateSelectorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TemplateSelectorWidget( QWidget *parent = nullptr );

    ~TemplateSelectorWidget();

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

} } }
