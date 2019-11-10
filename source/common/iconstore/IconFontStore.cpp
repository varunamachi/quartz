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

const QString IconFontStore::FONT_MATERIAL = "Material Icons";
const QString IconFontStore::FONT_FA_BRANDS = "Font Awesome 5 Brands";
const QString IconFontStore::FONT_FA_SOLID = "Font Awesome 5 Free";

std::unique_ptr<IconFontStore>
    IconFontStore::s_instance = std::unique_ptr<IconFontStore>(nullptr);

class CharIconPainter : public IIconFontPainter {
public:
    virtual void paint(IconFontStore* mat,
                       QPainter* painter,
                       const QRect& rect,
                       QIcon::Mode mode,
                       QIcon::State state,
                       const QVariantMap& options) {
        painter->save();
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
        auto fontName = options.value("fontName").toString();
        if (fontName != IconFontStore::FONT_MATERIAL) {
            drawSize = qRound(drawSize * 0.9);
        }

        color.setAlpha(185);
        painter->setPen(color);
        auto font = mat->font(fontName, drawSize);
        painter->setFont(font);
        painter->setRenderHint(QPainter::TextAntialiasing);
        painter->setRenderHint(QPainter::Antialiasing);
        painter->drawText(rect, text, {Qt::AlignTop | Qt::AlignVCenter});
        painter->restore();
    }
};

class IconFontEngine : public QIconEngine {

public:
    IconFontEngine(IconFontStore* mat,
                   CharIconPainter* painter,
                   const QVariantMap& options)
        : m_mat(mat)
        , m_painter(painter)
        , m_opts(options) {
    }

    virtual ~IconFontEngine();

    IconFontEngine* clone() const {
        return new IconFontEngine(m_mat, m_painter, m_opts);
    }

    void paint(QPainter* painter,
               const QRect& rect,
               QIcon::Mode mode,
               QIcon::State state) {
        m_painter->paint(m_mat, painter, rect, mode, state, m_opts);
    }

    QPixmap pixmap(const QSize& size, QIcon::Mode mode, QIcon::State state) {
        QPixmap pm(size);
        pm.fill(Qt::transparent);
        {
            QPainter p(&pm);
            p.setRenderHint(QPainter::Antialiasing);
            paint(&p, QRect{{0, 0}, size}, mode, state);
        }
        return pm;
    }

private:
    IconFontStore* m_mat;

    CharIconPainter* m_painter;

    QVariantMap m_opts;
};
IconFontEngine::~IconFontEngine() {
} // to shut the compiler up

struct IconFontStore::Data {

    Data()
        : m_painter(std::make_unique<CharIconPainter>()) {
    }

    QVariantMap m_defaultOpts;

    std::unique_ptr<CharIconPainter> m_painter;

    QStringList m_loadedFonts;
};

bool IconFontStore::init(const QByteArrayList& fonts) {
    static int loaded = false;
    auto index = -1;
    if (!loaded) {
        for (auto& fontData : fonts) {
            if (!(fontData.isNull() && fontData.isEmpty())) {
                index = QFontDatabase::addApplicationFontFromData(fontData);
                if (index != -1) {
                    auto ff = QFontDatabase::applicationFontFamilies(index);
                    if (!ff.empty()) {
                        QZ_INFO("Cmn:Font") << "Loaded font: " << ff.at(0);
                        loaded = true;
                    } else {
                        QZ_WARN("Cmn:Font") << "Material font file is empty";
                    }
                } else {
                    QZ_ERROR("Cmn:Font") << "Material font couldn't be loaded";
                }
            } else {
                QZ_ERROR("Cmn:Font") << "Invalid font data provided";
            }
        }
        s_instance = std::make_unique<IconFontStore>();
    }
    return loaded;
}

IconFontStore* IconFontStore::instance() {
    return s_instance.get();
}

IconFontStore::IconFontStore()
    : m_data(std::make_unique<Data>()) {
}

IconFontStore::~IconFontStore() {
}

void IconFontStore::setDefaultOption(const QString& name,
                                     const QVariant& value) {
    if (value.isValid()) {
        m_data->m_defaultOpts.insert(name, value);
    }
}

QIcon IconFontStore::icon(const QString& fontName,
                          int character,
                          const QVariantMap& options) {
    auto opts = options;
    opts["text"] = QString(QChar(static_cast<int>(character)));
    opts["fontName"] = fontName;
    return QIcon{new IconFontEngine(this, m_data->m_painter.get(), opts)};
}

QIcon IconFontStore::icon(const QString& fontName,
                          int character,
                          int size,
                          QColor color) {
    QVariantMap opts;
    if (size > 0) {
        opts["size"] = size;
    }
    if (color.isValid()) {
        opts["color"] = color;
    }
    return icon(fontName, character, opts);
}

QFont IconFontStore::font(const QString& fontName, int size) {
    QFont font(fontName);
    font.setPixelSize(size);
    return font;
}

QColor IconFontStore::getColor(QIcon::Mode mode,
                               QIcon::State state,
                               QVariantMap opts) {
    QColor res;
    QString modePostfix;
    switch (mode) {
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

QColor IconFontStore::getColor(QIcon::Mode mode) {
    auto palette = QApplication::palette();
    auto color = palette.color(QPalette::Text);
    if (mode == QIcon::Disabled) {
        color = palette.color(QPalette::AlternateBase);
    } else if (mode == QIcon::Selected) {
        color = palette.color(QPalette::Base);
    }
    return color;
}

} // namespace Quartz
