
#include <common/iconstore/Icons.h>

#include "IconNode.h"

namespace Quartz { namespace Ext { namespace IconFontExplorer {

struct IconNode::Data
{
    explicit Data(const IconInfo *iconInfo)
        : m_iconInfo(iconInfo)
    {

    }

    const IconInfo *m_iconInfo;
};

IconNode::IconNode(const IconInfo *iconInfo)
    : TreeNode(4)
    , m_data(std::make_unique<Data>(iconInfo))
{

}

IconNode::~IconNode()
{

}

QVariant IconNode::fieldValue(int column) const
{
    switch (column) {
    case 0: return m_data->m_iconInfo->m_code;
    case 1: return QString("0x%1").arg(m_data->m_iconInfo->m_code, 1, 16);
    case 2: return m_data->m_iconInfo->m_name;
    case 3: return m_data->m_iconInfo->m_font;
    }
    return {};
}

const IconInfo *IconNode::iconInfo() const
{
    return m_data->m_iconInfo;
}

QVector<std::shared_ptr<IconNode> > IconNode::roots()
{
    QVector<std::shared_ptr<IconNode>> roots;
    for (const auto &info : ICON_INFO) {
        roots.append(std::make_shared<IconNode>(&info));
    }
    return roots;
}



} } }
