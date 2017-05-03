#include <QVariant>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "../logger/Logging.h"
#include "DefaultStorageStrategy.h"

namespace Quartz {

const QString CREATE_QUERY =
        "CREATE TABLE Config ("
        "    key            TEXT,"
        "    value          BLOB,"
        "    domain         TEXT,"
        "PRIMARY KEY( key, domain ))";

const QString RETRIEVE_QUERY =
        "SELECT value FROM Config WHERE key = ? AND domain = ?";

const QString REMOVE_QUERY =
        "DELETE FROM Config WHERE key = ? AND domain = ?";

const QString STORE_QUERY =
        "INSERT OR REPLACE INTO Config( key, value, domain ) VALUES( ?, ?, ? )";


class DefaultStorageStrategy::Impl
{
public:
    explicit Impl( const QString &dbPath );

    bool createSchema();

    bool store( const QString &domain,
                const QString &key,
                const QByteArray &value );

    QByteArray retrieve( const QString &domain, const QString &key );

    bool remove( const QString &domain, const QString &key );

private:
    bool m_valid;
};



DefaultStorageStrategy::Impl::Impl( const QString &dbPath )
    : m_valid( false )
{
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setHostName( "localHost" );
    db.setDatabaseName( dbPath );

    if ( db.open() ) {
        QSqlQuery query( "SELECT name FROM sqlite_master "
                         "WHERE type='table' AND name='Config'" );
        if( query.exec() && query.next() ) {
            QZ_INFO( "Qz:Core:Config" ) << "Database initialization successful";
        }
        else {
            //Database does not exists
            QZ_INFO( "Qz:Core:Config" ) << "Creating database at "
                                        << dbPath;
            if( createSchema() ) {
                QZ_INFO( "Qz:Core:Config" )
                        << "Database creation successfull";
                m_valid = true;
            }
            else {
                QZ_ERROR( "Qz:Core:Config" )
                        << "Database creation failed: "
                        << db.lastError().text();
            }
        }
    }
    else {
        QZ_ERROR( "Qz:Core:Config" )
                << "Database creation failed: "
                << db.lastError().text();
    }
}


bool DefaultStorageStrategy::Impl::createSchema()
{
    QSqlQuery query{ CREATE_QUERY };
    bool result = query.exec();
    return result;
}

bool DefaultStorageStrategy::Impl::store( const QString &domain,
            const QString &key,
            const QByteArray &value )
{
    QSqlQuery query;
    query.prepare( STORE_QUERY );
    query.addBindValue( key );
    query.addBindValue( value );
    query.addBindValue( domain );
    bool result = query.exec();
    if( ! result ) {
        QZ_ERROR( "Qz:Core:Config" )
                << "Failed to store value for " << domain << "." << key
                << " -- " << query.lastError().text();

    }
    return result;
}

QByteArray DefaultStorageStrategy::Impl::retrieve( const QString &domain,
                     const QString &key )
{
    QSqlQuery query;
    query.prepare( RETRIEVE_QUERY );
    query.addBindValue( key );
    query.addBindValue( domain );
    bool result = query.exec();
    if( result && query.first() ) {
        auto rawData = query.value( 0 ).toByteArray();
        return rawData;
    }
    QZ_TRACE( "Qz:Core:Config" )
            << "Failed to retrieve value for " << domain << "." << key
            << " -- " << query.lastError().text();
    return QByteArray{};
}

bool DefaultStorageStrategy::Impl::remove( const QString &domain,
             const QString &key )
{
    QSqlQuery query;
    query.prepare( REMOVE_QUERY );
    query.addBindValue( key );
    query.addBindValue( domain );
    bool result = query.exec();
    if( ! result ) {
        QZ_ERROR( "Qz:Core:Config" )
                << "Failed to remove value for " << domain << "." << key
                << " -- " << query.lastError().text();

    }
    return result;
}

//#################### Interface
DefaultStorageStrategy::DefaultStorageStrategy( const QString &dbPath )
//    : m_impl( std::make_unique< Impl >( dbPath ))
    : m_impl( new Impl( dbPath ))
{

}


DefaultStorageStrategy::~DefaultStorageStrategy()
{

}


bool DefaultStorageStrategy::store( const QString &domain,
                                    const QString &key,
                                    const QByteArray &value )
{
    return m_impl->store( domain, key, value );
}


QByteArray DefaultStorageStrategy::retrieve( const QString &domain,
                                             const QString &key ) const
{
    return m_impl->retrieve( domain, key );
}


bool DefaultStorageStrategy::remove( const QString &domain,
                                     const QString &key )
{
    return m_impl->remove( domain, key );
}


}
