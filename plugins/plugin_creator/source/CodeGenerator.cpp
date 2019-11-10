
#include <QString>
#include <QDir>
#include <QFile>

#include <plugin_base/PluginLogging.h>

#include <common/templating/MustacheTemplateProcessor.h>
#include <common/templating/TemplateInstance.h>
#include <common/templating/Template.h>

#include "GenInfo.h"
#include "CodeGenerator.h"

namespace Quartz { namespace Ext { namespace Creator {

struct CodeGenerator::Data {
    Data(const GenInfo* info)
        : m_info(info) {
    }

    const GenInfo* m_info;

    QString m_lastError;
};

CodeGenerator::CodeGenerator(const GenInfo* info)
    : m_data(std::make_unique<Data>(info)) {
}

CodeGenerator::~CodeGenerator() {
}

bool CodeGenerator::generate(const QString& path, QStringList& out) {
    bool result = true;
    for (auto i = 0; i < m_data->m_info->numTemplateInstances(); ++i) {
        auto tinst = m_data->m_info->templateInstanceAt(i);
        result = this->generateForInstance(path, tinst, out) && result;
    }
    if (result) {
        QDir dir(path);
        QString msg;
        if (dir.exists("resources") || dir.mkdir("resources")) {
            QFile ptxt{dir.absoluteFilePath("resources/plugin.txt")};
            if (ptxt.open(QFile::ReadWrite)) {
                QTextStream fstream{&ptxt};
                fstream << "#Created By Quartz Plugin Creator\n"
                        << "id=" << m_data->m_info->id() << '\n'
                        << "name=" << m_data->m_info->name() << '\n'
                        << "display=" << m_data->m_info->display() << '\n'
                        << "ns=" << m_data->m_info->ns() << '\n'
                        << "version=0.0.0.0";
            } else {
                QZP_ERROR << "Failed to create plugin.txt at " << path
                          << "/resources";
                m_data->m_lastError = QObject::tr("Failed to create plugin.txt "
                                                  "in resource dir");
                result = false;
            }
        } else {
            QZP_ERROR << "Failed to create resource directory at " << path;
            m_data->m_lastError = QObject::tr("Failed to create resource dir "
                                              "at %1")
                                      .arg(path);
            result = false;
        }
        if (!result) {
            this->m_data->m_lastError = msg;
        }
    }
    if (result) {
        QZP_INFO << "Created plugin with id " << m_data->m_info->id() << " at "
                 << path;
        m_data->m_lastError = QObject::tr("Plugin %1 created successfully")
                                  .arg(m_data->m_info->id());
    } else {
        QZP_ERROR << "Could not create plugin with " << m_data->m_info->id()
                  << " at " << path;
        m_data->m_lastError = QObject::tr("Could not create plugin %1")
                                  .arg(m_data->m_info->id());
    }
    return result;
}

const QString& CodeGenerator::lastError() const {
    return m_data->m_lastError;
}

bool writeFile(const QString& path, const QString& content) {
    auto result = false;
    QFile file{path};
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        auto ba = content.toUtf8();
        result = ba.size() == file.write(ba);
    }
    if (!result) {
        QZP_ERROR << "Failed to create template output at " << path;
    }
    return result;
}

bool CodeGenerator::generateForInstance(const QString& path,
                                        const TemplateInstance* instance,
                                        QStringList& out) {
    auto result = true;
    MustacheTemplateProcessor proc;
    for (auto i = 0; i < instance->instanceOf()->numContents(); ++i) {
        const auto& content = instance->instanceOf()->contentAt(i);
        const auto vars = instance->allParams();
        const auto name = proc.process(content.m_name, vars);
        auto hasError = proc.hasError();
        if (!hasError) {
            proc.reset();
            auto filePath = path + "/" + name;
            auto fileContent = proc.process(content.m_text, vars);
            hasError = proc.hasError();
            if (!hasError) {
                if (writeFile(filePath, fileContent)) {
                    out.append(name);
                } else {
                    hasError = true;
                }
            }
        }
        if (hasError) {
            QZP_ERROR << "Failed to generate code for template instance "
                      << instance->name() << ": " << proc.lastError();
            result = false;
        }
        proc.reset();
    }
    return result;

    //    auto filePath = path + "/" + instance->name();
    //    QFile genFile(filePath);
    //    if (genFile.exists()) {
    //        QZP_ERROR << "Could not generate file " << instance->name()
    //                  << ", target already exists at: " << filePath;
    //        m_data->m_lastError = QObject::tr(
    //                    "Template Generation: output file %1 already exist,
    //                    cannot " "overwrite").arg(path);
    //        return false;
    //    }
    //    if (! genFile.open(QFile::ReadWrite)) {
    //        QZP_ERROR << "Could not generate file " << instance->name()
    //                  << ", failed to create" << filePath;
    //        m_data->m_lastError = QObject::tr(
    //                    "Template Generation: Failed to create file at %1")
    //                .arg(path);
    //        return false;
    //    }
    //    QTextStream stream{&genFile};
    //    MustacheTemplateProcessor tproc;
    //    auto result = tproc.process(instance->);
    //    if (! result) {
    //        m_data->m_lastError = tproc.lastError();
    //    }
    //    return result;
}

}}} // namespace Quartz::Ext::Creator
