#pragma once

#include <memory>
#include <functional>

#include <core/ext/IExtensionAdapter.h>

#include "../content_manager/ContentWidget.h"
#include "../QuartzBase.h"

class QWidget;

namespace Quartz {

class AbstractFileHandler;
class FileHandlerInfo;

class QUARTZ_BASE_API FileHandlerManager
        : public ContentWidget
        , public Ext::IExtensionAdapter
{
    Q_OBJECT

public:
    explicit FileHandlerManager(QWidget *parent = nullptr);

    ~FileHandlerManager();

    void registerFileHandler(
            std::shared_ptr<FileHandlerInfo> creator);

    void handle(const QString &path);

    const QString &extensionType() const;

    const QString &extensionAdapterName() const;

    bool handleExtension(Ext::Extension *extension);

    bool finalizeExtension();

    static const QString CONTENT_ID;
    static const QString CONTENT_NAME;
    static const QString CONTENT_KIND;
    static const QString ADAPTER_NAME;

private:
    struct Data;
    std::unique_ptr<Data> m_data;


};

}
