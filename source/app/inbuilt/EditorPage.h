#pragma once

#include <base/content_manager/ContentWidget.h>

namespace Quartz {

class EditorPage : public ContentWidget
{
    Q_OBJECT

public:
    explicit EditorPage(QWidget *parent = nullptr);

    ~EditorPage();

    static const QString CONTENT_ID;
    static const QString CONTENT_NAME;
    static const QString CONTENT_KIND;

private:
};

}

