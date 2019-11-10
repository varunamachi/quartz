#pragma once

#include <memory>

class QString;
class QStringList;

namespace Quartz {

class TemplateInstance;

namespace Ext { namespace Creator {

class GenInfo;

class CodeGenerator {
public:
    CodeGenerator(const GenInfo* info);

    virtual ~CodeGenerator();

    virtual bool generate(const QString& path, QStringList& out);

    const QString& lastError() const;

protected:
    virtual bool generateForInstance(const QString& path,
                                     const TemplateInstance* instance,
                                     QStringList& out);

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}} // namespace Ext::Creator
} // namespace Quartz
