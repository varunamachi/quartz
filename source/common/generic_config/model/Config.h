#pragma once

#include <memory>

#include <QHash>

#include "../../QuartzCommon.h"
#include "../../model_view/TreeNode.h"

class QString;

namespace Quartz {

class Param;
class Group;

class QUARTZ_COMMON_API Config : public TreeNode
{
public:
    Config( const QString &id, const QString &name );

    ~Config();

    const QString & id() const;

    const QString & name() const;

    int numChildParams() const;

    Param * childParamAt( int index ) const;

    void addChildParameter( std::shared_ptr< Param > param );

    int numGroups() const;

    Group * groupAt( int index ) const;

    void addGroup( std::shared_ptr< Group > group );

    const Param * param( const QString &id ) const;

    Param * param( const QString &id );

    bool registerParam( Param *param );

    QVariant fieldValue( int field ) const override;

    std::unique_ptr< Config > clone() const;

    const QHash<QString, Param *> & allParams() const;
private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
