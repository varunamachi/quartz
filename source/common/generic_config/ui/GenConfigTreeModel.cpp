
#include "GenConfigTreeModel.h"

#include "../model/Config.h"

namespace Quartz {


const QVector<QString> HEADERS{
    QObject::tr("Name"),
    QObject::tr("Value")
};

struct GenConfigTreeModel::Data
{
    explicit Data() { }

    Config * m_config = nullptr;

};

GenConfigTreeModel::GenConfigTreeModel(QObject *parent)
    : AbstractTreeModel{
          parent,
          AbstractTreeModel::Options(2, false, false, HEADERS)}
    , m_data(std::make_unique<Data>())
{
}

GenConfigTreeModel::~GenConfigTreeModel()
{

}

void GenConfigTreeModel::setConfig(Config *config)
{
    beginResetModel();
    m_data->m_config = config;
    endResetModel();

}

TreeNode *GenConfigTreeModel::rootAt(int /*rowIndex*/) const
{
    return m_data->m_config;
}

int GenConfigTreeModel::rootCount() const
{
    if (m_data->m_config != nullptr) {
        return m_data->m_config->numChildren() != 0 ? 1 : 0;
    }
    return 0;
}


}
