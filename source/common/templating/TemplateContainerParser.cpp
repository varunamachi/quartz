
#include <QFile>
#include <QString>
#include <QByteArray>
#include <QDomElement>
#include <QDomNodeList>
#include <QDomNode>
#include <QDomNamedNodeMap>

#include <core/logger/Logging.h>

#include "../generic_config/ops/ConfigParser.h"
#include "../generic_config/model/Config.h"
#include "Template.h"
#include "TemplateContainerParser.h"


namespace Quartz {

TemplateContainerParser::TemplateContainerParser()
{

}

TemplateContainerParser::~TemplateContainerParser()
{

}

QVector<std::shared_ptr<Template>> TemplateContainerParser::parse(
        const QString &content)
{
    QVector<std::shared_ptr<Template>> tmpls;
    if (content.isNull()) {
        QZ_ERROR("Qz:Cmn:Tmpl")
                << "Invalid content given to general param parser";
        return tmpls;
    }
    QDomDocument doc;
    QString errorMsg("");
    int errorLine = 0;
    if (doc.setContent(content, false, &errorMsg, &errorLine)) {
        auto root = doc.documentElement();
        if (root.tagName() == "templates") {
            auto tmplLists = root.elementsByTagName("template");
            for (auto i = 0; i < tmplLists.size(); ++ i) {
                auto tmplNode = tmplLists.at(i);
                auto tmpl = parse(tmplNode.toElement());
                if (tmpl != nullptr) {
                    std::shared_ptr<Template> cp = std::move(tmpl);
                    tmpls.append(cp);
                }
                else {
                    QZ_ERROR("Qz:Cmn:Tmpl")
                            << "Could not parse one of the 'template' tags";
                }
            }
            if (tmplLists.isEmpty()) {
                QZ_ERROR("Qz:Cmn:Tmpl")
                        << "Could not find 'template' tags inside 'templates'";
            }
        }
        else {
            QZ_ERROR("Qz:Cmn:Tmpl")
                    << "Could not find root 'templates' tag";
        }
    }
    else {
        QZ_ERROR("Qz:Cmn:Tmpl")
                << "Failed to read config XML content at " << errorLine
                << " Msg: " << errorMsg;

    }
    return tmpls;
}

std::unique_ptr<Config> parseConfig(const QDomElement &root) {
    std::unique_ptr<Config> config;
    auto configNodeList = root.elementsByTagName("config");
    if (configNodeList.size() == 1) {
        auto configNode = configNodeList.at(0);
        ConfigParser configParser;
        config = configParser.parse(configNode.toElement());
        if (config == nullptr) {
            QZ_ERROR("Qz:Cmn:Tmpl")
                    << "Failed to parse template parameters";
        }
    } else {
        auto msg = configNodeList.isEmpty() ? "Could not find config tag"
                                            : "Too many config tags found";
        QZ_ERROR("Qz:Cmn:Tmpl") << msg;
    }
    return config;
}

int readContent(Template *tmpl, const QDomElement &root)
{
    QString content;
    auto count = 0;
    auto cntNodeList = root.elementsByTagName("content");
    for (auto i = 0; i < cntNodeList.size(); ++ i) {
        auto contentNode = cntNodeList.at(i);
        auto name = contentNode.toElement().attribute("name");
        auto children = contentNode.toElement().childNodes();
        auto content = QStringLiteral("");
        for (auto i = 0; i < children.size(); ++ i) {
            auto child = children.at(i);
            if (child.isCDATASection()) {
                auto cdata = child.toCDATASection();
                content = cdata.data();
                break;
            } else if (child.nodeName() == "file") {
                auto path = child.toElement().attribute("path");
                QFile file(path);
                if (file.open(QFile::ReadOnly)) {
                    content = file.readAll();
                    break;
                }
                else {
                    QZ_ERROR("Qz:Cmn:Tmpl")
                            << "Failed to open template file at '"
                            << path << "'";
                }
            }
        }
        if (content.size() != 0) {
            count = count + content.size();
            tmpl->addContent({name, content});
        }
    }
    return count;
}

std::unique_ptr<Template> TemplateContainerParser::parse(
        const QDomElement &root)
{
    std::unique_ptr<Template> tmpl;
    auto name = root.attribute("name");
    if (! name.isEmpty()) {
        auto config = parseConfig(root);
        if (config != nullptr) {
            tmpl = std::make_unique<Template>(name);
            tmpl->setConfig(std::move(config));
            auto count = readContent(tmpl.get(), root);
            if (count == 0) {
                QZ_ERROR("Qz:Cmn:Tmpl")
                        << "Found empty template content";
            }
        }
        else {
            QZ_ERROR("Qz::Cmn:Tmpl")
                    << "Could not find valid config in tempalte container";
        }
    } else {
        QZ_ERROR("Qz:Cmn:Tmpl")
                << "Could not read the template name attribute";
    }
    return tmpl;
}


}
