#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QStringList>
#include <QString>

#include <core/logger/Logging.h>

#include "Template.h"
#include "TemplateUtils.h"
#include "TemplateContainerParser.h"

namespace Quartz {

QVector<std::shared_ptr<Template>> TemplateUtils::templatesInDir(QDir dir) {
    QVector<std::shared_ptr<Template>> templates;
    auto list = dir.entryInfoList();
    TemplateContainerParser parser;
    for (int i = 0; i < list.size(); ++i) {
        auto entry = list.at(i);
        if (entry.suffix() == "xml") {
            auto inputPath = entry.absoluteFilePath();
            QFile file(inputPath);
            if (file.exists() && file.open(QFile::ReadOnly)) {
                QZ_INFO("Qz:Cmn:Tmpl")
                    << "Reading template file at " << inputPath;
                QTextStream stream{&file};
                auto content = stream.readAll();
                auto tmps = parser.parse(content);
                for (auto i = 0; i < tmps.length(); ++i) {
                    templates.append(tmps.at(i));
                }
            } else {
                QZ_ERROR("Qz:Cmn:Tmpl")
                    << "Could not open template file " << inputPath;
            }
        }
    }
    return templates;
}

} // namespace Quartz
