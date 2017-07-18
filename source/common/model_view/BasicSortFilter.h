#pragma once

#include <memory>

#include <QSortFilterProxyModel>

namespace Quartz {

class BasicSortFilter : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit BasicSortFilter( QObject *parent );

    ~BasicSortFilter();

    bool filterAcceptsRow( int sourceRow,
                           const QModelIndex &srcParent ) const override;

public slots:
    void setExpression( const QString &expression );

protected:
    bool lessThan( const QModelIndex &left,
                   const QModelIndex &right ) const override;

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

}
