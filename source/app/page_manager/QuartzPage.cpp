
#include "QuartzPage.h"

namespace Quartz {

struct QuartzPage::Data
{
public:
    Data( const QString &pageId,
          const QString &category,
          const QString &categoryName,
          const QString &displayName )
        : m_pageId( pageId )
        , m_categoryId( category )
        , m_categoryName( categoryName )
        , m_displayName( displayName )
    {

    }

    QString m_pageId;

    QString m_categoryId;

    QString m_categoryName;

    QString m_displayName;
};


QuartzPage::QuartzPage( const QString &pageId,
                        const QString &category,
                        const QString &categoryName,
                        const QString &displayName,
                        QWidget *parent )
    : QWidget( parent )
    //        , m_data( std::make_unique< Data > ( pageId,
    //                                             category,
    //                                             categoryName,
    //                                             displayName ))
    , m_data( new Data( pageId, category, categoryName, displayName ))
{

}

QuartzPage::~QuartzPage()
{

}

const QString & QuartzPage::pageId() const
{
    return m_data->m_pageId;
}

const QString & QuartzPage::pageCategoryId() const
{
    return m_data->m_categoryId;
}

const QString & QuartzPage::pageDisplayName() const
{
    return m_data->m_displayName;
}

const QString & QuartzPage::pageCategoryName() const
{
    return m_data->m_categoryName;
}

}


