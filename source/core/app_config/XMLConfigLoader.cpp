

#include <QString>
#include <QVariant>
#include <QFile>
#include <QColor>
#include <QImage>
#include <QtXml/QDomDocument>

#include "../logger/Logging.h"
#include "XMLConfigLoader.h"

namespace Quartz {

static QVariant variantFrom(const QDomNode& typeAttr,
                            const QDomNode& valueAttr) {
    auto value = valueAttr.nodeValue();
    auto is = [&](const QString& tp) -> bool {
        return typeAttr.nodeValue().compare(tp, Qt::CaseInsensitive) == 0;
    };
    if (is("int")) {
        auto base = 10;
        if (value.startsWith("0x", Qt::CaseInsensitive)) {
            base = 16;
        } else if (value.startsWith('0')) {
            base = 8;
        }
        bool ok = true;
        auto ival = value.toInt(&ok, base);
        if (!ok) {
            QZ_WARN("Qz:Core:Config")
                << "Invalid string for integer given: " << value;
        }
        return QVariant(ival);
    } else if (is("bool")) {
        auto bval = value.compare("true", Qt::CaseInsensitive) == 0;
        return QVariant(bval);
    } else if (is("double")) {
        bool ok = true;
        auto dval = value.toDouble(&ok);
        if (!ok) {
            QZ_WARN("Qz:Core:Config")
                << "Invalid string for double given: " << value;
        }
        return QVariant(dval);
    } else if (is("color")) {
        bool ok = false;
        if (value.startsWith('#')) {
            auto argb = value.right(1).toUInt(&ok, 16);
            if (ok) {
                return QVariant(QColor(argb));
            }
        }
        if (!ok) {
            QZ_WARN("Qz:Core:Config")
                << "Invalid string for color given: " << value;
        }
    } else if (is("image")) {
        // Image path
        QFile imageFile(value);
        if (imageFile.exists()) {
            return QVariant(QImage(value));
        } else {
            QZ_WARN(("Qz:Core:Confog"))
                << "An image file is not found at path: " << value;
        }
    } else {
        return QVariant(value);
    }
    return QVariant{};
}

XMLConfigLoader::XMLConfigLoader(AbstractConfigLoader::StoreFunc storeFunc)
    : AbstractConfigLoader(storeFunc) {
}

XMLConfigLoader::~XMLConfigLoader() {
}

bool XMLConfigLoader::load(const QByteArray content) const {
    if (!content.isNull()) {
        QZ_ERROR("Qz:Core:Config") << "XML Config Loader: Invalid content "
                                      "given";
        return false;
    }
    QDomDocument doc;
    QString errorMsg("");
    int errorLine = 0;
    if (doc.setContent(content, false, &errorMsg, &errorLine)) {
        auto root = doc.documentElement();
        if (root.tagName() != "quartz-config") {
            QZ_ERROR("Qz:Core:Config") << "XML Config Loader: Could not find "
                                          "tag 'quartz-config'";
            return false;
        }
        auto configList = root.elementsByTagName("config");
        for (int i = 0; i < configList.size(); ++i) {
            auto configNode = configList.at(i);
            auto domainNode = configNode.parentNode();
            QString domain = "";
            if (domainNode.nodeName() == "domain") {
                auto attrMap = domainNode.attributes();
                auto domainNameAttr = attrMap.namedItem("name");
                if (!domainNameAttr.isNull()) {
                    domain = domainNameAttr.nodeValue();
                }
            }
            auto configAttrMap = configNode.attributes();
            auto keyAttr = configAttrMap.namedItem("name");
            auto valAttr = configAttrMap.namedItem("value");
            auto typeAttr = configAttrMap.namedItem("type");
            if (keyAttr.isNull() || valAttr.isAttr()) {
                QZ_WARN("Qz:Core:Config")
                    << "XML Config Loader: Invalid attribute found in "
                       "domain "
                    << (domain.isEmpty() ? "[GLOBAL]" : domain);
            } else {
                auto variant = variantFrom(typeAttr, valAttr);
                if (variant.isValid()) {
                    storeFunc()(domain, keyAttr.nodeValue(), variant);
                }
            }
        }
    } else {
        QZ_ERROR("Qz:Core:Config")
            << "XML Config Loader: Validation failed: " << errorMsg
            << " - Error Line: " << errorLine;
    }
    return false;
}

} // namespace Quartz
