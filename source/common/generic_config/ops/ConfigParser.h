#pragma once

#include <memory>
#include <functional>

#include <QVector>
#include <QVariant>

#include "../../QuartzCommon.h"

class QByteArray;
class QDomElement;

using ValueProvider = std::function<QVariant(const QString &key)>;

namespace Quartz {

class Config;
class Param;
class Param;
class Group;
class TreeNode;

class QUARTZ_COMMON_API ConfigParser
{
public:
    ConfigParser(ValueProvider = nullptr);

    virtual ~ConfigParser();

    virtual QVector<std::shared_ptr<Config>> parse(const QByteArray &content);

    std::unique_ptr<Config> parse(const QDomElement &configRoot);


protected:
    std::shared_ptr<Param> parseParam(
            Config &config,
            TreeNode *parent,
            const QDomElement &paramNode);

    std::shared_ptr<Group> parseGroup(
            Config &config,
            TreeNode *parent,
            const QDomElement &groupNode);

private:
    struct Data;
    std::unique_ptr<Data> m_data;

};

}
