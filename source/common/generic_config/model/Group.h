#pragma once

#include <memory>

#include "../../QuartzCommon.h"
#include "../../model_view/TreeNode.h"

class QString;

namespace Quartz {

class Param;

class QUARTZ_COMMON_API Group : public TreeNode
{
public:
    Group( const QString &id,
           const QString &name,
           const QString &description,
           TreeNode *parent );

    ~Group();

    const QString & id() const;

    const QString & name() const;

    const QString & description() const;

    void addParam( std::shared_ptr< Param > param );

    int numParams() const;

    Param * paramAt( int index ) const;

    Param * paramAt( int index );

    int numSubGroups() const;

    void addSubGroup( std::shared_ptr< Group > subGroup );

    Group * subGroupAt( int index );

    QVariant data( int field ) const override;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
