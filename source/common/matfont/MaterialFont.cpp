#include <QString>
#include <QVariant>
#include <QIcon>
#include <QFont>
#include <QPainter>
#include <QRect>
#include <QIconEngine>
#include <QApplication>
#include <QPalette>
#include <QFile>
#include <QFontDatabase>

#include <core/logger/Logging.h>

#include "MaterialFont.h"

namespace Quartz {

class MaterialCharIconPainter: public IMaterialFontPainter
{
public:


    virtual void paint(MaterialFont* mat,
                       QPainter* painter,
                       const QRect& rect,
                       QIcon::Mode mode,
                       QIcon::State state,
                       const QVariantMap& options)
    {
        painter->save();
        QString text;
        QColor color = mat->getColor(mode, state, options);
        painter->setPen(color);
        int drawSize = qRound(rect.height() * 0.9);
        painter->setFont(mat->font(drawSize));
        painter->restore();
    }

};



class MaterialIconFontEngine : public QIconEngine
{

public:

    MaterialIconFontEngine(
            MaterialFont* mat,
            MaterialCharIconPainter* painter,
            const QVariantMap& options)
        : m_mat(mat)
        , m_painter(painter)
        , m_opts(options)
    {
    }

    virtual ~MaterialIconFontEngine() {}

    MaterialIconFontEngine* clone() const
    {
        return new MaterialIconFontEngine(
                    m_mat,
                    m_painter,
                    m_opts);
    }

    void paint(QPainter* painter,
               const QRect& rect,
               QIcon::Mode mode,
               QIcon::State state)
    {
        m_painter->paint(m_mat,
                         painter,
                         rect,
                         mode,
                         state,
                         m_opts);
    }

    QPixmap pixmap(const QSize& size, QIcon::Mode mode, QIcon::State state)
    {
        QPixmap pm{size};
        pm.fill( Qt::transparent ); // we need transparency
        {
            QPainter p(&pm);
            paint(&p, QRect{{ 0,0 },size}, mode, state);
        }
        return pm;
    }

private:
    MaterialFont *m_mat;

    MaterialCharIconPainter *m_painter;

    QVariantMap m_opts;
};


struct MaterialFont::Data {

    Data() : m_painter{new MaterialCharIconPainter()}
    {

    }

    QVariantMap m_defaultOpts;

    std::unique_ptr<MaterialCharIconPainter> m_painter;

    QString m_fontName;

};

MaterialFont::MaterialFont()
    : m_data{}
{

}

MaterialFont::~MaterialFont()
{

}

bool MaterialFont::init()
{
    static int loaded = false;
    auto index = -1;
    if (!loaded) {
//        Q_INIT_RESOURCE(common);
        QFile res("://fonts/MaterialIcons-Regular.ttf");
        if(res.open(QIODevice::ReadOnly)) {
            QByteArray fontData( res.readAll() );
            res.close();
            index = QFontDatabase::addApplicationFontFromData(fontData);
            if (index != -1) {
                auto fontFam = QFontDatabase::applicationFontFamilies(index);
                if (!fontFam.empty()) {
                    this->m_data->m_fontName = fontFam.at(0);
                    loaded = true;
                }
            }
        }
    }
    if (!loaded) {
        QZ_ERROR("Cmn:MatFont") << "Material font couldn't be loaded";
    }
    return loaded;
}


void MaterialFont::setDefaultOption(const QString &name,
                                    const QVariant &value)
{
    if (value.isValid()) {
        m_data->m_defaultOpts.insert(name, value);
    }
}

QIcon MaterialFont::icon(MatIcon character,
                         const QVariantMap &options)
{
    auto opts = options;
    opts["text"] = QString{QChar(static_cast<int>(character))};
    return QIcon{new MaterialIconFontEngine(
                    this, m_data->m_painter.get(), options)};
}

QIcon MaterialFont::icon(MatIcon character)
{
    return icon(character, QVariantMap{});
}


QFont MaterialFont::font(int size)
{
    QFont font{m_data->m_fontName};
    font.setPixelSize(size);
    return font;
}

QColor MaterialFont::getColor(
        QIcon::Mode mode,
        QIcon::State state,
        QVariantMap opts)
{
    QColor res = QApplication::palette().text().color();
    QString modePostfix;
    switch(mode) {
    case QIcon::Disabled: modePostfix = "-disabled"; break;
    case QIcon::Active: modePostfix = "-active"; break;
    case QIcon::Selected: modePostfix = "-selected"; break;
    default: break;
    }
    QString statePostfix = state == QIcon::Off ? "-off" : "";
    auto key = "color" + modePostfix + statePostfix;

    if (opts.contains(key)) {
        res = opts[key].value<QColor>();
    } else if (m_data->m_defaultOpts.contains(key)) {
        res = m_data->m_defaultOpts[key].value<QColor>();
    }
    return res;
}


}

