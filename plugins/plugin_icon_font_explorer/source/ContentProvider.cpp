
#include "ContentProvider.h"
#include "MainWidget.h"

namespace Quartz { namespace Ext { namespace IconFontExplorer {

/********************** Provider ************************************/
const QString ContentProvider::EXTENSION_ID("qzp.icon_font_explorer.provider."
                                            "content");
const QString ContentProvider::EXTENSION_NAME("Quartz Icon Font Explorer  "
                                              "Content");

struct ContentProvider::Data {
    explicit Data() {
    }

    QVector<ContentWidget*> m_widgets;
};

ContentProvider::ContentProvider()
    : AbstractContentProvider(EXTENSION_ID, EXTENSION_NAME)
    , m_data(std::make_unique<Data>()) {
    m_data->m_widgets.append(new MainWidget());
}

ContentProvider::~ContentProvider() {
}

bool ContentProvider::init() {
    return true;
}

bool ContentProvider::destroy() {
    return true;
}

QVector<ContentWidget*> ContentProvider::widgets() {
    return m_data->m_widgets;
}

}}} // namespace Quartz::Ext::IconFontExplorer
