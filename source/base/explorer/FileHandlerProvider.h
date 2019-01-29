#pragma once

#include <functional>
#include <memory>

#include <QIcon>

#include <core/ext/Extension.h>

class QWidget;
class QIcon;

namespace Quartz {

class AbstractFileHandler;
using FHCreator = std::function<AbstractFileHandler *(QWidget *parent)>;

struct FileHandlerCreator
{
    QString m_name;
    QStringList m_extensions;
    FHCreator m_creatorFunc;
    QIcon m_icon;
};

class FileHandlerProvider : public Ext::Extension
{
public:
    FileHandlerProvider(const QString &extID,
                        const QString &extName,
                        const FileHandlerCreator &creator);

    ~FileHandlerProvider() override;

    const FileHandlerCreator & creator() const;

    static const QString EXTENSION_TYPE;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}
