#pragma once

#include <memory>

#include <QVector>

#include "../QuartzCore.h"

namespace Quartz {

class QUARTZ_CORE_API History {
public:
    /**
     * @brief History Simple class to hold command/navigation history
     * @param overIndex - use last index to be one more than the size of the
     *  history. This is useful for command history
     */
    History(bool overIndex = true);

    ~History();

    bool isValid() const;

    const QString& get() const;

    const QString& next() const;

    const QString& prev() const;

    void add(const QString& val);

    const QVector<QString>& all() const;

    void clear();

    const static QString EMPTY_STRING;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

} // namespace Quartz
