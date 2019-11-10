
#include <QTime>
#include <QDateTime>

#include <common/iconstore/IconFontStore.h>

#include "Msg.h"

namespace Quartz {

const auto COL_INF = QColor{24, 122, 220};
const auto COL_WRN = QColor{179, 143, 0};
const auto COL_ERR = QColor{204, 41, 0};

struct Msg::Data {

    Data(int id,
         const QString& msg,
         NotificationType type,
         QTime time,
         QDateTime dateTime)
        : m_id(id)
        , m_msg(msg)
        , m_type(type)
        , m_time(time)
        , m_dateTime(dateTime) {
    }

    int m_id;

    QString m_msg;

    NotificationType m_type;

    QTime m_time;

    QDateTime m_dateTime;
};

Msg::Msg(int id,
         const QString& msg,
         const NotificationType type,
         const QTime& time,
         const QDateTime& dateTime)
    : TreeNode(3)
    , m_data(std::make_unique<Data>(id, msg, type, time, dateTime)) {
}

Msg::~Msg() {
}

QVariant Msg::fieldValue(int column) const {
    switch (column) {
    case 0: {
        switch (m_data->m_type) {
        case NotificationType::Info: return "INFO";
        case NotificationType::Warning: return "WARNING";
        case NotificationType::Error: return "ERROR";
        }
    }; break;
    case 1: return m_data->m_time;
    case 2: return m_data->m_msg;
    }
    return QVariant{};
}

QVariant Msg::decoration(int column) const {
    if (column == 0) {
        switch (m_data->m_type) {
        case NotificationType::Info:
            return getIcon(MatIcon::InfoOutline, COL_INF);
        case NotificationType::Warning:
            return getIcon(MatIcon::Warning, COL_WRN);
        case NotificationType::Error: return getIcon(MatIcon::Error, COL_ERR);
        }
    }
    return QVariant{};
}

NotificationType Msg::type() const {
    return m_data->m_type;
}

const QTime& Msg::time() const {
    return m_data->m_time;
}

const QDateTime& Msg::dateTime() const {
    return m_data->m_dateTime;
}

const QString& Msg::text() {
    return m_data->m_msg;
}

} // namespace Quartz
