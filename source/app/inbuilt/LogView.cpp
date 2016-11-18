
#include <QTextStream>
#include <QAbstractItemModel>
#include <QDateTime>
#include <QTreeView>
#include <QVBoxLayout>
#include <QHeaderView>

#include <core/logger/LogUtil.h>
#include <core/logger/ILogFormatter.h>
#include <core/logger/LogMessage.h>
#include <core/logger/LogStructures.h>

#include "LogView.h"

Q_DECLARE_METATYPE( std::shared_ptr< Quartz::LogData > );

namespace Quartz {

namespace {
    QString sevString( Logger::LogLevel level )
    {
        switch( level ) {
        case Logger::LogLevel::Trace  : return "TRACE";
        case Logger::LogLevel::Debug  : return "DEBUG";
        case Logger::LogLevel::Info   : return "INFO ";
        case Logger::LogLevel::Warn   : return "WARNG";
        case Logger::LogLevel::Error  : return "ERROR";
        case Logger::LogLevel::Fatal  : return "FATAL";
        case Logger::LogLevel::Special: return "*****";
        case Logger::LogLevel::Method : return "*****";
        }
        return "";
    }

}

struct LogData
{
    explicit LogData( const Logger::LogMessage *msg )
        : m_time( msg->time() )
        , m_logLevel( msg->logLevel() )
        , m_moduleName( msg->moduleName() )
        , m_logMessage( msg->message() )
    {

    }

    QDateTime m_time;

    Logger::LogLevel m_logLevel;

    QString m_moduleName;

    QString m_logMessage;
};

LogModel::LogModel( QObject *parent )
    : QAbstractItemModel( parent )
{
}

LogModel::~LogModel()
{

}

QModelIndex LogModel::index( int row,
                             int column,
                             const QModelIndex &parent ) const
{
    Q_UNUSED( parent )
    return createIndex(row, column);
}

QModelIndex LogModel::parent( const QModelIndex &child ) const
{
    Q_UNUSED( child )
    return QModelIndex();
}

int LogModel::rowCount( const QModelIndex &parent ) const
{
    Q_UNUSED( parent )
    return m_msgs.size();
}

int LogModel::columnCount( const QModelIndex &parent ) const
{
    Q_UNUSED( parent )
    return 4;
}

QVariant LogModel::data( const QModelIndex &index, int role ) const
{
    if( ! index.isValid() || index.row() >= m_msgs.size() ) {
        return QVariant();
    }
    if ( role == Qt::TextAlignmentRole ) {
        return int ( Qt::AlignLeft | Qt::AlignVCenter );
    }
    else if ( role == Qt::DisplayRole ) {
        auto msg = m_msgs.at( index.row() );
        switch ( index.column() ) {
        case 0: return msg->m_time.toString( "yyyy-MM-dd hh:mm:ss" );
        case 1: return sevString( msg->m_logLevel );
        case 2: return msg->m_moduleName;
        case 3: return msg->m_logMessage;
        }
    }
    else if( role == Qt::SizeHintRole ) {
        switch ( index.column() ) {
        case 0: return 35;
        case 1: return 5;
        case 2: return 40;
        }
    }
    return QVariant();
}

bool LogModel::hasChildren(const QModelIndex &parent) const
{
    if(! parent.isValid()) {
        return true;
    }
    return false;
}

QVariant LogModel::headerData( int section,
                               Qt::Orientation orientation,
                               int role ) const
{
    Q_UNUSED( orientation );
    if ( role == Qt::TextAlignmentRole ) {
        return int( Qt::AlignLeft | Qt::AlignVCenter );
    }
    else if ( role == Qt::DisplayRole ) {
        switch( section ) {
        case 0: return tr( "Time" );
        case 1: return tr( "Severity" );
        case 2: return tr( "Modue" );
        case 3: return tr( "Message" );
        }
    }
    return QVariant();
}

void LogModel::add( std::shared_ptr< LogData > msg )
{
    beginInsertRows( QModelIndex{}, m_msgs.size(), m_msgs.size() + 1 );
//    beginResetModel();
    m_msgs.append( msg );
//    endResetModel();
    endInsertRows();
}

void LogModel::clear()
{
    beginResetModel();
    m_msgs.clear();
    endResetModel();
}


struct LogView::Data
{
    LogModel *m_model;

    QTreeView *m_view;
};

const QString LogView::LOG_TARGET_ID{ "Quartz.LogView" };
const QString LogView::VIEW_ID{ "Quartz.LogView" };
const QString LogView::VIEW_DISPLAY_NAME{ "Log" };
const QString LogView::VIEW_CATEGORY{ "Quartz.Inbuilt" };

LogView::LogView( QWidget *parent )
    : QuartzView( VIEW_ID, VIEW_CATEGORY, VIEW_DISPLAY_NAME, parent )
    , Logger::AbstractLogTarget( LOG_TARGET_ID )
    , m_data( new Data{} )
{
    qRegisterMetaType< std::shared_ptr< Quartz::LogData >>();

    m_data->m_model = new LogModel{ this };
    m_data->m_view  = new QTreeView{ this };
    m_data->m_view->setModel( m_data->m_model );
    connect( this, &LogView::sigLogMessage, m_data->m_model, &LogModel::add );

    auto layout = new QVBoxLayout{ this };
    layout->addWidget( m_data->m_view );
    this->setLayout( layout );
    layout->setContentsMargins( QMargins{} );
    m_data->m_view->setContentsMargins( QMargins{} );
    m_data->m_view->setSortingEnabled( true );
    m_data->m_view->setWordWrap( false );
    m_data->m_view->setAutoScroll( true );
    m_data->m_view->setAlternatingRowColors( true );
    m_data->m_view->setRootIsDecorated( false );
}

LogView::~LogView()
{

}

void LogView::flush()
{
    //nothing here...
}

void LogView::write( const Logger::LogMessage *message )
{
    auto logData = std::make_shared< LogData >( message );
    emit sigLogMessage( logData );
}

void LogView::clear()
{
    m_data->m_model->clear();
}

void LogView::write( QString &&/*logString*/ )
{

}




}
