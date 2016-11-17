#pragma once

#include <QAbstractItemModel>

#include <core/logger/AbstractLogTarget.h>

#include <base/view_manager/QuartzView.h>


namespace Quartz {

struct LogData;
class LogModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit LogModel( QObject *parent );

    ~LogModel();

    QModelIndex index( int row, int column, const QModelIndex &parent ) const;

    QModelIndex parent( const QModelIndex &child ) const;

    int rowCount( const QModelIndex &parent ) const;

    int columnCount( const QModelIndex &parent ) const;

    QVariant data( const QModelIndex &index, int role ) const;

public slots:
    void add( const Logger::LogMessage *msg );

    void clear();

private:
    QVector< std::shared_ptr< LogData >> m_msgs;

};


class LogView : public QuartzView
              , public Logger::AbstractLogTarget
{
    Q_OBJECT
public:
    explicit LogView( QWidget *parent );

    ~LogView();

    void flush() override;

    void write( const Logger::LogMessage *message ) override;

    static const QString LOG_TARGET_ID;

    static const QString VIEW_ID;

    static const QString VIEW_DISPLAY_NAME;

    static const QString VIEW_CATEGORY;

public slots:
    void clear();

signals:
    void sigLogMessage( const Logger::LogMessage *message );

protected:
    void write( QString &&logString ) override;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
