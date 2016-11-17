#pragma once

#include <core/logger/AbstractLogTarget.h>

#include <base/view_manager/QuartzView.h>


namespace Quartz {

class LogView : public QuartzView
              , public Logger::AbstractLogTarget
{
    Q_OBJECT
public:
    explicit LogView( QWidget *parent );

    ~LogView();

    void flush() override;

    void write( const Logger::LogMessage *message ) override;

public slots:
    void clear();

    void onLogMessage( const QString &message );

signals:
    void sigLogMessage( const QString &message );

protected:
    void write( QString &&logString ) override;

//    void format( const Logger::LogMessage *message );


private:
    struct Data;
    std::unique_ptr< Data > m_data;





};

}
