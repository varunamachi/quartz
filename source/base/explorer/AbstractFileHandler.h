#pragma once

#include <memory>

#include <QWidget>

#include "../QuartzBase.h"

class QStringList;
class QFile;

namespace Quartz {

class QUARTZ_BASE_API AbstractFileHandler : public QWidget
{
    Q_OBJECT

public:
    AbstractFileHandler(QWidget *parent = nullptr)
        : QWidget(parent)
    {

    }

    virtual ~AbstractFileHandler() {}

    virtual bool handle(const QString &path) = 0;

    virtual QString path() const = 0;

    virtual bool close() = 0;

    virtual bool save() = 0;

};

}
