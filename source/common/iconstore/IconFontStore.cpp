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

#include "IconFontStore.h"

namespace Quartz {

std::unique_ptr<IconFontStore> IconFontStore::s_instance =
        std::unique_ptr<IconFontStore>(nullptr);

class CharIconPainter: public IIconFontPainter
{
public:


    virtual void paint(IconFontStore* mat,
                       QPainter* painter,
                       const QRect& rect,
                       QIcon::Mode mode,
                       QIcon::State state,
                       const QVariantMap& options)
    {
        painter->save();
//        painter->setFe
        QString text = options.value("text").toString();
        QColor color;
        if (options.contains("color")) {
            color = options["color"].value<QColor>();
        } else {
            color = mat->getColor(mode, state, options);
        }
        auto drawSize = rect.height();
        if (options.contains("size")) {
            drawSize = options["size"].toInt();
        }
        color.setAlpha(175);
        painter->setPen(color);
        auto font = mat->font(qRound(drawSize * 0.9));
        painter->setFont(font);
        painter->setRenderHint(QPainter::Antialiasing);
        painter->drawText(
                    rect,
                    text,
                    { Qt::AlignTop| Qt::AlignVCenter });
        painter->restore();
    }

};



class IconFontEngine : public QIconEngine
{

public:

    IconFontEngine(
            IconFontStore* mat,
            CharIconPainter* painter,
            const QVariantMap& options)
        : m_mat(mat)
        , m_painter(painter)
        , m_opts(options)
    {
    }

    virtual ~IconFontEngine() {}

    IconFontEngine* clone() const
    {
        return new IconFontEngine(
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
        pm.fill(Qt::transparent);
        {
            QPainter p(&pm);
            paint(&p, QRect{{ 0,0 }, size}, mode, state);
        }
        return pm;
    }

private:
    IconFontStore *m_mat;

    CharIconPainter *m_painter;

    QVariantMap m_opts;
};


struct IconFontStore::Data {

    Data() : m_painter{std::make_unique<CharIconPainter>()}
    {

    }

    QVariantMap m_defaultOpts;

    std::unique_ptr<CharIconPainter> m_painter;

    QString m_fontName;

};

bool IconFontStore::init(const QByteArray &fontData)
{
    static int loaded = false;
    auto index = -1;
    if (!loaded) {
        if (!(fontData.isNull() && fontData.isEmpty())) {
            index = QFontDatabase::addApplicationFontFromData(fontData);
            if (index != -1) {
                auto fontFam = QFontDatabase::applicationFontFamilies(index);
                if (!fontFam.empty()) {
                    s_instance = std::make_unique<IconFontStore>();
                    s_instance->m_data->m_fontName = fontFam.at(0);
                    loaded = true;
                } else {
                    QZ_WARN("Cmn:MatFont") << "Material font file is empty";
                }
            } else {
                QZ_ERROR("Cmn:MatFont") << "Material font couldn't be loaded";
            }
        } else {
            QZ_ERROR("Cmn:MatFont") << "Invalid font data provided";
        }
    }
    return loaded;
}

IconFontStore * IconFontStore::instance() {
    return s_instance.get();
}

IconFontStore::IconFontStore()
    : m_data{std::make_unique<Data>()}
{

}

IconFontStore::~IconFontStore()
{

}

void IconFontStore::setDefaultOption(const QString &name,
                                    const QVariant &value)
{
    if (value.isValid()) {
        m_data->m_defaultOpts.insert(name, value);
    }
}

QIcon IconFontStore::icon(MatIcon character,
                         const QVariantMap &options)
{
    auto opts = options;
    opts["text"] = QString{QChar(static_cast<int>(character))};
    return QIcon{new IconFontEngine(
                    this, m_data->m_painter.get(), opts)};
}

QIcon IconFontStore::icon(MatIcon character, int size, QColor color)
{
    QVariantMap opts;
    opts["text"] = QString{QChar(static_cast<int>(character))};;
    if (size > 0) {
        opts["size"] = size;
    }
    if (color.isValid()) {
        opts["color"] = color;
    }
    return icon(character, opts);
}

//QIcon MaterialFont::icon(MatIcon character)
//{
//    return icon(character, QVariantMap{});
//}


QFont IconFontStore::font(int size)
{
    QFont font{m_data->m_fontName};
    font.setPixelSize(size);
    return font;
}

QColor IconFontStore::getColor(
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
    case QIcon::Normal: modePostfix = ""; break;
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

