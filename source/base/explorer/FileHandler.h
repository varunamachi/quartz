#pragma once

#include <memory>

#include <base/content_manager/ContentWidget.h>

namespace Quartz {

class MonacoEditor;

class EditorPage : public ContentWidget
{
    Q_OBJECT

public:
    explicit EditorPage(QWidget *parent = nullptr);

    ~EditorPage();

    MonacoEditor * editor() const;

    static const QString CONTENT_ID;
    static const QString CONTENT_NAME;
    static const QString CONTENT_KIND;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}

