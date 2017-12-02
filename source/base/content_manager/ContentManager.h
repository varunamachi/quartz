#pragma once

#include <memory>

#include <QWidget>

#include <core/ext/IExtensionAdapter.h>

#include "../QuartzBase.h"

namespace Quartz {

class ContentWidget;

class QUARTZ_BASE_API ContentManager : public QWidget
                                     , public Ext::IExtensionAdapter
{
    Q_OBJECT

public:
    explicit ContentManager( QWidget *parent = nullptr );

    ~ContentManager();

    bool addContent( ContentWidget *content );

    bool removeContent( const QString &contentId );

    ContentWidget * content( const QString &contentId );

    QVector< ContentWidget *> contentsOfKind( const QString &kind );

    int removeKind( const QString &kind );

    void selectContent( const QString &contentId );

public:
    const QString &extensionType() const override;

    const QString &extensionAdapterName() const override;

    bool handleExtension( Ext::Extension *ext ) override;

    bool finalizeExtension() override;

    static const QString ADAPTER_NAME;

signals:
    void sigContentSelected( ContentWidget *widget );

    void sigContentAdded( ContentWidget *widget );

    void sigContentRemoved( const QString &contentId );

private:
    void setupLayout();

    struct Data;
    std::unique_ptr< Data > m_data;



};

}
