#pragma once

#include <core/ext/IExtensionAdapter.h>

#include "../selector/TreeModel.h"

namespace Quartz {

class GeneralNodeTree : public TreeModel
                      , public Ext::IExtensionAdapter
{
    Q_OBJECT

public:
    explicit GeneralNodeTree(QObject *parent = nullptr);

    const QString & extensionType() const override;

    const QString & extensionAdapterName() const override;

    bool handleExtension(Ext::Extension *extension) override;

    bool finalizeExtension() override;


};



}
