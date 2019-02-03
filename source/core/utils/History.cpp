

#include "History.h"

namespace Quartz {

enum class HistoryDirection
{
    Backward,
    Forward,
    None
};

const QString History::EMPTY_STRING = QStringLiteral("");

struct History::Data
{
    int m_historyIndex = 0;

    HistoryDirection m_historyDirection = HistoryDirection::None;

    QVector<QString> m_history;
};


History::History()
    : m_data(std::make_unique<Data>())
{

}

History::~History()
{

}

bool History::isValid() const
{
    return ! m_data->m_history.isEmpty()
            && m_data->m_historyIndex >= 0
            && m_data->m_historyIndex <= m_data->m_history.size();
}

const QString &History::get() const
{
    if (m_data->m_historyIndex < m_data->m_history.size()) {
        return m_data->m_history[ m_data->m_historyIndex ];
    }
    return EMPTY_STRING;
}

const QString &History::next() const
{
    if (isValid()) {
        if (m_data->m_historyIndex < m_data->m_history.size()) {
            ++ m_data->m_historyIndex;
        }
        m_data->m_historyDirection = HistoryDirection::Forward;
    }
    return get();
}

const QString &History::prev() const
{
    if (isValid()) {
        if (m_data->m_historyIndex > 0) {
            -- m_data->m_historyIndex;
        }
        m_data->m_historyDirection = HistoryDirection::Backward;
    }
    return get();
}

void History::add(const QString &historyItem)
{
    if (m_data->m_history.isEmpty()
            || m_data->m_history.last() != historyItem) {
        m_data->m_history.push_back(historyItem);
    }
    m_data->m_historyIndex = m_data->m_history.size();
    m_data->m_historyDirection = HistoryDirection::None;
}

const QVector<QString> &History::all() const
{
    return m_data->m_history;
}

void History::clear()
{
    m_data->m_history.clear();
    m_data->m_historyIndex = 0;
    m_data->m_historyDirection = HistoryDirection::None;
}

}
