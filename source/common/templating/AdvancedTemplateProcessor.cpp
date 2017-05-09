#include <QFile>

#include <core/logger/Logging.h>

#include "AdvancedTemplateProcessor.h"

namespace Quartz {

const QString ADV_END_TOKEN = QString{ "%>" };
const QString ADV_START_TOKEN = QString{ "<%" };
const QString ADV_BLK_START_TOKEN = QString{ ":>" };


struct AdvancedTemplateProcessor::Data
{
    explicit Data()
    {

    }

};

AdvancedTemplateProcessor::AdvancedTemplateProcessor(
        const TemplateProcessor::Variables &vars )
    : TemplateProcessor{ vars }
    , m_data{ new Data{}}
{

}

AdvancedTemplateProcessor::~AdvancedTemplateProcessor()
{
}


bool AdvancedTemplateProcessor::process( QString &input,
                                         QTextStream &output )
{
    bool result = false;
    auto firstBlocks = input.split( ADV_END_TOKEN );
    foreach( QString one, firstBlocks ) {
        if( one.contains( ADV_START_TOKEN )) {
            auto loopBlock = one.split( ADV_START_TOKEN );
            if( loopBlock.size() == 2 ) {
                //now parse the for loop
                //if could be tricky since we need to evaluate the condition
                //Also if we are using parent's process function to replace
                //  variables then we need a way to temporarily add variables
                //  to variable map so that loop variables get replaced
            }
            else {
                //template is wrong
            }
        }
    }

    return result;
}

}
