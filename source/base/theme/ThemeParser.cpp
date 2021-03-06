#include <QString>
#include <QByteArray>
#include <QDomElement>
#include <QDomNodeList>
#include <QDomNode>
#include <QDomNamedNodeMap>
#include <QColor>
#include <QImage>
#include <QGradient>
#include <QPalette>
#include <QFile>

#include <core/logger/Logging.h>
#include <common/templating/MustacheTemplateProcessor.h>

#include "Theme.h"
#include "ThemeParser.h"

namespace Quartz {

void updatePalatte(const QString& name, QColor value, QPalette& palette) {
    if (name == "Window") {
        palette.setColor(QPalette::Window, value);
    } else if (name == "WindowText") {
        palette.setColor(QPalette::WindowText, value);
    } else if (name == "Base") {
        palette.setColor(QPalette::Base, value);
    } else if (name == "AlternateBase") {
        palette.setColor(QPalette::AlternateBase, value);
    } else if (name == "ToolTipBase") {
        palette.setColor(QPalette::ToolTipBase, value);
    } else if (name == "ToolTipText") {
        palette.setColor(QPalette::ToolTipText, value);
    } else if (name == "Text") {
        palette.setColor(QPalette::Text, value);
    } else if (name == "Button") {
        palette.setColor(QPalette::Button, value);
    } else if (name == "ButtonText") {
        palette.setColor(QPalette::ButtonText, value);
    } else if (name == "BrightText") {
        palette.setColor(QPalette::BrightText, value);
    } else if (name == "Link") {
        palette.setColor(QPalette::Link, value);
    } else if (name == "Highlight") {
        palette.setColor(QPalette::Highlight, value);
    } else if (name == "HighlightedText") {
        palette.setColor(QPalette::HighlightedText, value);
    }
}

ThemeParser::ThemeParser() {
}

std::unique_ptr<Theme> ThemeParser::parse(const QString& content) {
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
            if (!name.isEmpty()) {
                theme = std::make_unique<Theme>(name);
            } else {
                QZ_ERROR("Qz:Cmn:Theme") << "Theme name is empty";
            }
        } else {
            QZ_ERROR("Qz:Cmn:Theme") << "Failed to find theme tag at the root";
        }
    } else {
        QZ_ERROR("Qz:Cmn:Theme") << "Failed to read config XML content at "
                                 << errorLine << " Msg: " << errorMsg;
    }
    return theme;
}

bool ThemeParser::parseDeclarations(const QDomElement& el, Theme& theme) {
    auto result = true;
    for (auto node = el.firstChildElement("item"); !node.isNull();
         node = el.nextSiblingElement("item")) {
        auto type = node.attribute("type");
        auto name = node.attribute("name");
        auto value = node.attribute("value");
        if (type != "" && name != "" && value != "") {
            theme.addDeclaration(name, value);
            if (type == "color") {
                auto color = QColor{value};
                if (!color.isValid()) {
                    QZ_WARN("Qz:Theme") << "Invalid value " << value
                                        << " given for color " << name;
                }
                theme.setColor(name, color);
            } else if (type == "image") {
                auto img = QImage(value);
                if (img.isNull()) {
                    QZ_WARN("Qz:Theme") << "Invalid value " << value
                                        << " give for image " << name;
                }
                theme.setImage(name, img);
            } else if (type == "gradient") {
                QZ_WARN("Qz:Theme") << "Gradients are not supported at "
                                       "this time, name: "
                                    << name;
            } else {
                QZ_WARN("Qz:Theme") << "Invalid declaration type '" << type
                                    << "' given. Ignoring...";
            }
        } else {
            QZ_WARN("Qz:Theme") << "Invalid declaration provided";
        }
    }
    return result;
}

bool ThemeParser::parsePalettes(const QDomElement& el, Theme& /*theme*/) {
    auto result = true;
    QPalette palette;
    for (auto node = el.firstChildElement("color"); !node.isNull();
         node = el.nextSiblingElement("color")) {
        auto name = node.attribute("name");
        auto value = node.attribute("value");
        if (name != "" && value != "") {
            auto color = QColor{value};
            if (!color.isValid()) {
                QZ_WARN("Qz:Theme") << "Invalid value " << value
                                    << " given for palatte color" << name;
                result = false;
            }
            updatePalatte(name, color, palette);
        } else {
            QZ_WARN("Qz:Theme") << "Invalid palatte information given";
            result = false;
        }
    }
    return result;
}

bool ThemeParser::parseStylesheet(const QDomElement& el, Theme& theme) {
    auto result = false;
    auto css = QString();
    // First check if this file refers to a CSS file
    ///@TODO - relative path? then what is the root? From executable path?
    /// User configuration directory?
    for (auto node = el.firstChildElement("file"); !node.isNull();
         node = el.nextSiblingElement("file")) {
        auto path = node.attribute("path");
        ///@TODO Need to expand path into absolute
        QFile file(path);
        if (file.exists() && file.open(QFile::ReadOnly)) {
            css = QString{file.readAll()};
            result = true;
        } else {
            QZ_WARN("Qz:Theme") << "Invalid CSS file '" << path << "' given";
        }
    }
    // If we were successful in reading the CSS file, we ignore the CDATA
    // section
    if (!result) {
        // consider only the first content tag
        auto content = el.firstChildElement("content");
        auto children = content.toElement().childNodes();
        for (auto i = 0; i < children.size(); ++i) {
            auto child = children.at(i);
            if (child.isCDATASection()) {
                css = child.toCDATASection().data();
            }
        }
    }
    if (result) {
        // Resolve mustache variables
        MustacheTemplateProcessor tmplProcessor;
        auto resolved = tmplProcessor.process(css, theme.declarations());
        result = !tmplProcessor.hasError();
        if (result) {
            theme.setApplicationCSS(resolved);
        } else {
            QZ_WARN("Qz:Theme") << "Failed to generate application css: "
                                << tmplProcessor.lastError();
        }
    }
    return result;
}

} // namespace Quartz
