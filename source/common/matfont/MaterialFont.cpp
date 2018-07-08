#include <QString>
#include <QVariant>
#include <QIcon>
#include <QFont>
#include <QPainter>
#include <QRect>

#include "MaterialFont.h"

namespace Quartz {

MaterialFont::MaterialFont()
{

}

MaterialFont::~MaterialFont()
{

}

bool MaterialFont::init()
{
    return false;
}

void MaterialFont::addNamedCodepoint(const QString &/*name*/, int /*codePoint*/)
{

}

QHash<QString, int> MaterialFont::namedCodePoints()
{
    return QHash<QString, int>{};
}

void MaterialFont::setDefaultOption(const QString &/*name*/,
                                    const QVariant &/*value*/)
{

}

QVariant MaterialFont::defaultOption(const QString &/*name*/)
{
    return QVariant{};
}

QIcon MaterialFont::icon(int /*character*/, const QVariantMap &/*options*/)
{
    return QIcon{};
}

QIcon MaterialFont::icon(const QString &/*name*/, const QVariantMap &/*options*/)
{
    return QIcon{};
}

QIcon MaterialFont::icon(MaterialFontPainter */*painter*/,
                         const QVariantMap &/*optionMap*/)
{
    return QIcon{};
}

QIcon MaterialFont::icon(int /*character*/)
{
    return QIcon{};
}

QIcon MaterialFont::icon(const QString &/*name*/)
{
    return QIcon{};
}

QIcon MaterialFont::icon(MaterialFontPainter */*painter*/)
{
    return QIcon{};
}

QFont MaterialFont::font(int /*size*/)
{
    return QFont{};
}

void MaterialFont::give(const QString &/*name*/,
                        MaterialFontPainter */*painter*/)
{

}



}

