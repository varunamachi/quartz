#pragma once

#include <common/model_view/TreeNode.h>

namespace Quartz {

struct IconInfo;

namespace Ext { namespace IconFontExplorer {

class IconNode : public TreeNode {
public:
    IconNode(const IconInfo* iconInfo);

    ~IconNode() override;

    QVariant fieldValue(int column) const override;

    const IconInfo* iconInfo() const;

    static QVector<std::shared_ptr<IconNode>> roots();

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}} // namespace Ext::IconFontExplorer
} // namespace Quartz
