#pragma once

#include <memory>
#include <functional>

#include <QAbstractItemModel>

#include "../QuartzCommon.h"

namespace Quartz {

class TreeNode;



class QUARTZ_COMMON_API AbstractTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    using SetterFunc = std::function< void(TreeNode *node, QVariant value)>;

    struct Options {
        Options(int nf = 1,
                bool sel = false,
                bool flat = true,
                QVector<QString> headers = {})
            : numFields(nf)
            , selectable(sel)
            , flat(flat)
            , headers(headers)
        {

        }

        int numFields;
        bool selectable;
        bool flat;
        QVector<QString> headers;
    };

    AbstractTreeModel(QObject *parent = nullptr, Options opts = Options{});

    virtual ~AbstractTreeModel();

    QModelIndex index(int row,
                       int column,
                       const QModelIndex &parent) const override;


    QModelIndex parent(const QModelIndex &child) const override;

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(
            int section,
            Qt::Orientation o,
            int role) const override;

    bool hasChildren(const QModelIndex &parent) const override;

    bool setData(const QModelIndex &index,
                 const QVariant &value,
                 int role) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

protected:
    virtual TreeNode * rootAt(int rowIndex) const = 0;

    virtual int rootCount() const = 0;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}
