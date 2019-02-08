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
        "PRIMARY KEY(key, domain))";

const QString RETRIEVE_QUERY =
        "SELECT value FROM Config WHERE key = ? AND domain = ?";

const QString REMOVE_QUERY =
        "DELETE FROM Config WHERE key = ? AND domain = ?";

const QString STORE_QUERY =
        "INSERT OR REPLACE INTO Config(key, value, domain) VALUES(?, ?, ?)";

class DefaultStorageStrategy::Data
{
public:
    explicit Data(const QString &dbPath)
        : m_dbPath(dbPath)
    {

    }

    bool createSchema()
    {
        QSqlQuery query(CREATE_QUERY);
        bool result = query.exec();
        return result;
    }

    QString m_dbPath;

    bool m_valid;
};

DefaultStorageStrategy::DefaultStorageStrategy(const QString &dbPath)
    : m_data(std::make_unique<Data>(dbPath))
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localHost");
    db.setDatabaseName(dbPath);

    if (db.open()) {
        QSqlQuery query("SELECT name FROM sqlite_master "
                         "WHERE type='table' AND name='Config'");
        if (query.exec() && query.next()) {
            QZ_INFO("Qz:Core:Config") << "Database initialization successful";
        } else {
            //Database does not exists
            QZ_INFO("Qz:Core:Config") << "Creating database at "
                                        << dbPath;
            if (m_data->createSchema()) {
                QZ_INFO("Qz:Core:Config")
                        << "Database creation successfull";
                m_data->m_valid = true;
            } else {
                QZ_ERROR("Qz:Core:Config")
                        << "Database creation failed: "
                        << db.lastError().text();
            }
        }
    } else {
        QZ_ERROR("Qz:Core:Config")
                << "Database creation failed: "
                << db.lastError().text();
    }
}

DefaultStorageStrategy::~DefaultStorageStrategy()
{

}

bool DefaultStorageStrategy::store(const QString &domain,
            const QString &key,
            const QByteArray &value)
{
    QSqlQuery query;
    query.prepare(STORE_QUERY);
    query.addBindValue(key);
    query.addBindValue(value);
    query.addBindValue(domain);
    bool result = query.exec();
    if (! result) {
        QZ_ERROR("Qz:Core:Config")
                << "Failed to store value for " << domain << "." << key
                << " -- " << query.lastError().text();

    }
    return result;
}

QByteArray DefaultStorageStrategy::retrieve(const QString &domain,
                                            const QString &key) const
{
    QSqlQuery query;
    query.prepare(RETRIEVE_QUERY);
    query.addBindValue(key);
    query.addBindValue(domain);
    bool result = query.exec();
    if (result && query.first()) {
        auto rawData = query.value(0).toByteArray();
        return rawData;
    }
    return QByteArray{};
}

bool DefaultStorageStrategy::remove(const QString &domain,
                                    const QString &key)
{
    QSqlQuery query;
    query.prepare(REMOVE_QUERY);
    query.addBindValue(key);
    query.addBindValue(domain);
    bool result = query.exec();
    if (! result) {
        QZ_ERROR("Qz:Core:Config")
                << "Failed to remove value for " << domain << "." << key
                << " -- " << query.lastError().text();

    }
    return result;
}

QVariantHash DefaultStorageStrategy::allFromDomain(
        const QString &domain,
        BlobDecoder decoder) const
{
    QVariantHash values;
    const auto q = QStringLiteral(
                "SELECT * FROM Config WHERE domain = ?"
    );
    QSqlQuery query;
    query.prepare(q);
    query.addBindValue(domain);
    bool result = query.exec();
    if (result) {
        while(query.next()) {
            auto key = query.value("key").toString();
            auto blob = query.value("value").toByteArray();
            values[key] = decoder(blob);
        }
    }
    return values;
}

}
