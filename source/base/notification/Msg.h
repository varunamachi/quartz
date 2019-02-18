#pragma once

#include <common/model_view/TreeNode.h>

class QTime;
class QDateTime;

namespace Quartz {

enum class NotificationType : int
{
    Info,
    Warning,
    Error,
};

class Msg : public TreeNode
{
public:
    Msg(int id,
        const QString &msg,
        const NotificationType type,
        const QTime &time,
        const QDateTime &dateTime);

    ~Msg();

    QVariant fieldValue(int column) const override;

    QVariant decoration(int column) const override;

    NotificationType type() const;

    const QTime & time() const;

    const QDateTime & dateTime() const;

    const QString & text();

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}
