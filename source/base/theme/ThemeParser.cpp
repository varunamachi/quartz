#include <QString>
#include <QByteArray>
#include <QDomElement>
#include <QDomNodeList>
#include <QDomNode>
#include <QDomNamedNodeMap>
#include <QColor>

#include <core/logger/Logging.h>


#include "Theme.h"
#include "ThemeParser.h"

namespace Quartz {


ThemeParser::ThemeParser()
{

}

std::unique_ptr<Theme> ThemeParser::parse(const QString &content)
{
    std::unique_ptr<Theme> theme;
    if (content.isNull()) {
        QZ_ERROR("Qz:Cmn:Theme") << "Theme content empty";
        return theme;
    }
    QDomDocument doc;
    QString errorMsg;
    int errorLine = 0;
    if (doc.setContent(content, false, &errorMsg, &errorLine)) {
        auto root = doc.documentElement();
        if (root.tagName() == "theme") {
            auto name = root.toElement().attribute("name");
            if (! name.isEmpty()) {
                theme = std::make_unique<Theme>(name);
            } else {
                QZ_ERROR("Qz:Cmn:Theme") << "Theme name is empty";
            }
        } else {
            QZ_ERROR("Qz:Cmn:Theme") << "Failed to find theme tag at the root";
        }
    } else {
        QZ_ERROR("Qz:Cmn:Theme")
                << "Failed to read config XML content at " << errorLine
                << " Msg: " << errorMsg;
    }
    return theme;
}

bool ThemeParser::parseDeclarations(const QDomElement &el, Theme & theme)
{
    auto result = true;
    for (auto node = el.firstChildElement("item");
         !node.isNull();
         node = el.nextSiblingElement("item")) {
        auto type = node.attribute("type");
        auto name = node.attribute("name");
        auto value = node.attribute("value");
        if (type != "" && name != "" && value != "") {
            if (type == "color") {
                auto color = QColor{value};
                if (!color.isValid()) {
                    QZ_WARN("Qz:Theme") << "Invalid color value " << value
                                        << " for color " << name;
                }
                theme.setColor(name, color);
            } else if (type == "image") {
                //take only path??
            } else if (type == "gradient") {
                //Ignore for now
            } else {
                QZ_WARN("Qz:Theme") << "Invalid declaration type '" << type
                                    << "' given. Ignoring...";
            }
        } else {
            QZ_WARN("Qz:Theme") << "Invalid declaration provided";
        }
    }
    return true;
}

bool ThemeParser::parsePalettes(const QDomElement &el, Theme & /*theme*/)
{
    for (auto node = el.firstChildElement("color");
         !node.isNull();
         node = el.nextSiblingElement("color")) {
        //prase item
    }
    return false;
}

bool ThemeParser::parseStylesheet(const QString &/*content*/, Theme & /*theme*/)
{
    return false;
}

}
