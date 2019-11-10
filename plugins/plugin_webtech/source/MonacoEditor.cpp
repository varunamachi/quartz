#include <QWebEngineView>
#include <QVBoxLayout>
#include <QFile>
#include <QWebChannel>
#include <QThread>
#include <QFileInfo>
#include <QQueue>
#include <QFileDialog>

#include <core/job_manager/JobManager.h>
#include <core/utils/ScopedOperation.h>

#include <plugin_base/PluginLogging.h>
#include <plugin_base/PluginContext.h>

#include "MonacoEditor.h"
#include "conf/Conf.h"

/*
#define m_data->exec(statement) \
    if (!m_data->m_initialized) {                                       \
        m_data->m_pendingCommands.append([=]() {                        \
            m_data->m_monaco->page()->runJavaScript(statement);         \
        });                                                             \
    } else {                                                            \
        m_data->m_monaco->page()->runJavaScript(statement);             \
    }                                                                   \
*/

namespace Quartz { namespace Ext { namespace WebTech {

const QHash<QString, QString> EXT_LANG = {
    {"", "plaintext"},
    {"conf", "plaintext"},
    {"config", "plaintext"},
    {"txt", "plaintext"},
    {"gitignore", "plaintext"},
    {"cmake", "cmake"},
    {"json", "json"},
    {"bowerrc", "json"},
    {"jshintrc", "json"},
    {"jscsrc", "json"},
    {"eslintrc", "json"},
    {"babelrc", "json"},
    {"bat", "bat"},
    {"cmd", "bat"},
    {"coffee", "coffeescript"},
    {"c", "c"},
    {"h", "c"},
    {"cpp", "cpp"},
    {"cc", "cpp"},
    {"cxx", "cpp"},
    {"hpp", "cpp"},
    {"hh", "cpp"},
    {"hxx", "cpp"},
    {"cs", "csharp"},
    {"csx", "csharp"},
    {"cake", "csharp"},
    {"css", "css"},
    {"dockerfile", "dockerfile"},
    {"dart", "dart"},
    {"fs", "fsharp"},
    {"fsi", "fsharp"},
    {"ml", "fsharp"},
    {"mli", "fsharp"},
    {"fsx", "fsharp"},
    {"fsscript", "fsharp"},
    {"go", "go"},
    {"handlebars", "handlebars"},
    {"hbs", "handlebars"},
    {"html", "html"},
    {"htm", "html"},
    {"shtml", "html"},
    {"xhtml", "html"},
    {"mdoc", "html"},
    {"jsp", "html"},
    {"asp", "html"},
    {"aspx", "html"},
    {"jshtm", "html"},
    {"ini", "ini"},
    {"properties", "ini"},
    {"gitconfig", "ini"},
    {"java", "java"},
    {"jav", "java"},
    {"js", "javascript"},
    {"es6", "javascript"},
    {"jsx", "javascript"},
    {"less", "less"},
    {"lua", "lua"},
    {"md", "markdown"},
    {"markdown", "markdown"},
    {"mdown", "markdown"},
    {"mkdn", "markdown"},
    {"mkd", "markdown"},
    {"mdwn", "markdown"},
    {"mdtxt", "markdown"},
    {"mdtext", "markdown"},
    {"dax", "msdax"},
    {"msdax", "msdax"},
    {"m", "objective-c"},
    {"php", "php"},
    {"php4", "php"},
    {"php5", "php"},
    {"phtml", "php"},
    {"ctp", "php"},
    {"dats", "postiats"},
    {"sats", "postiats"},
    {"hats", "postiats"},
    {"pq", "powerquery"},
    {"pqm", "powerquery"},
    {"ps1", "powershell"},
    {"psm1", "powershell"},
    {"psd1", "powershell"},
    {"jade", "pug"},
    {"pug", "pug"},
    {"py", "python"},
    {"rpy", "python"},
    {"pyw", "python"},
    {"cpy", "python"},
    {"gyp", "python"},
    {"gypi", "python"},
    {"r", "r"},
    {"rhistory", "r"},
    {"rprofile", "r"},
    {"rt", "r"},
    {"cshtml", "razor"},
    {"redis", "redis"},
    {"rb", "ruby"},
    {"rbx", "ruby"},
    {"rjs", "ruby"},
    {"gemspec", "ruby"},
    {"pp", "ruby"},
    {"rs", "rust"},
    {"rlib", "rust"},
    {"sb", "sb"},
    {"scss", "scss"},
    {"sol", "sol"},
    {"sql", "sql"},
    {"st", "st"},
    {"iecst", "st"},
    {"iecplc", "st"},
    {"lc3lib", "st"},
    {"swift", "swift"},
    {"ts", "typescript"},
    {"tsx", "typescript"},
    {"vb", "vb"},
    {"xml", "xml"},
    {"dtd", "xml"},
    {"ascx", "xml"},
    {"csproj", "xml"},
    {"config", "xml"},
    {"wxi", "xml"},
    {"wxl", "xml"},
    {"wxs", "xml"},
    {"xaml", "xml"},
    {"svg", "xml"},
    {"svgz", "xml"},
    {"yaml", "yaml"},
    {"yml", "yaml"},
    {"scm", "scheme"},
    {"ss", "scheme"},
    {"sch", "scheme"},
    {"rkt", "scheme"},
    {"clj", "clojure"},
    {"clojure", "clojure"},
    {"sh", "shell"},
    {"bash", "shell"},
    {"pl", "perl"},
    {"azcli", "azcli"},
    {"cls", "apex"},
};

QString readJS(QFile& file) {
    QString content;
    content.reserve(static_cast<int>(file.size()));
    QTextStream stream{&file};
    while (!stream.atEnd()) {
        auto line = stream.readLine();
        for (int i = 0; i < line.size(); ++i) {
            switch (line.at(i).toLatin1()) {
            case '\\': content.append("\\\\"); break;
            case '`': content.append("\\`"); break;
            case '\"': content.append("\\\""); break;
            case '$': content.append("\\$"); break;
            default: content.append(line.at(i)); break;
            }
        }
        content.append("\\n");
    }
    return content;
}

const QString MonacoEditor::escape(const QString& /*orig*/) {
    //@TODO Implement above escape logic for strings
    return "";
}

struct MonacoEditor::Data {
    explicit Data(MonacoEditor* parent)
        : m_monaco(new QWebEngineView(parent))
        , m_qzwrapper(new SharedObject(parent))
        , m_initialized(false)
        , m_dirty(false) {
        auto channel = new QWebChannel(parent);
        m_monaco->page()->setWebChannel(channel);
        channel->registerObject(QStringLiteral("qzwrapper"), m_qzwrapper);
    }

    QWebEngineView* m_monaco;

    SharedObject* m_qzwrapper;

    bool m_initialized;

    bool m_dirty;

    QString m_path;

    QFile m_file;

    QQueue<std::function<void()>> m_pendingCommands;

    static QStringList s_extensions;

    inline void exec(const QString& statement) {
        auto st = QString("if (window.editor) { %1 }").arg(statement);
        if (!m_initialized) {
            m_pendingCommands.append([=]() {
                m_monaco->page()->runJavaScript(st);
            });
        } else {
            m_monaco->page()->runJavaScript(st);
        }
    }

    inline void exec(const QString& statement,
                     QWebEngineCallback<const QVariant&> callback) {
        auto st = QString("if (window.editor) { %1 }").arg(statement);
        if (!m_initialized) {
            m_pendingCommands.append([=]() {
                m_monaco->page()->runJavaScript(st, callback);
            });
        } else {
            m_monaco->page()->runJavaScript(st, callback);
        }
    }
};

MonacoEditor::MonacoEditor(QWidget* parent)
    : AbstractFileHandler(parent)
    , m_data(std::make_unique<Data>(this)) {
    auto layout = new QVBoxLayout();
    layout->addWidget(m_data->m_monaco);
    QFile file{":/resources/index.html"};
    if (file.open(QFile::ReadOnly)) {
        const QString html = file.readAll();
        m_data->m_monaco->setHtml(html, QUrl("qrc:/resources/"));
        file.close();

    } else {
        m_data->m_monaco->setHtml(tr("<h2>Failed to load index.html</h2>"));
    }

    this->setLayout(layout);

    connect(m_data->m_monaco, &QWebEngineView::loadFinished, [this]() {
        m_data->m_initialized = true;
        while (!m_data->m_pendingCommands.empty()) {
            auto func = m_data->m_pendingCommands.takeFirst();
            func();
        }
    });

    setTheme(conf<QString>(Conf::EDITOR_THEME, "vs-dark"));
    setRulerAt(conf<int>(Conf::EDITOR_VLINE_NUM, 80));
    showMinimap(conf<bool>(Conf::EDITOR_SHOW_MINIMAP, false));
    showLineNumber(conf<bool>(Conf::EDITOR_SHOW_LINENUM, true));

    connect(
        confman(),
        &ConfigManager::configChanged,
        this,
        [this](const QString& key, const QVariant& val, const QString domain) {
            if (domain == Conf::CONF_DOMAIN) {
                if (key == Conf::EDITOR_THEME) {
                    this->setTheme(val.toString());
                } else if (key == Conf::EDITOR_VLINE_NUM) {
                    this->setRulerAt(val.toInt());
                } else if (key == Conf::EDITOR_SHOW_MINIMAP) {
                    this->showMinimap(val.toBool());
                } else if (key == Conf::EDITOR_SHOW_LINENUM) {
                    this->showLineNumber(val.toBool());
                }
            }
        });
}

MonacoEditor::~MonacoEditor() {
}

SharedObject* MonacoEditor::controller() const {
    return m_data->m_qzwrapper;
}

void MonacoEditor::setContent(const QString& ct, const QString& lang) {
    m_data->exec("setContent(`" + ct
                 + "`);"
                   "monaco.editor.setModelLanguage("
                   "window.editor.getModel(), "
                   "`"
                 + lang + "`);");
}

void MonacoEditor::setLanguage(const QString& language) {
    m_data->exec("monaco.editor.setModelLanguage(window.editor.getModel(), "
                 "`"
                 + language + "`);");
}

void MonacoEditor::setTheme(const QString& theme) {
    m_data->exec("monaco.editor.setTheme(`" + theme + "`)");
}

void MonacoEditor::showMinimap(bool show) {
    m_data->exec(QStringLiteral("window.editor.updateOptions({"
                                "minimap: {"
                                "enabled: ")
                 + (show ? "true" : "false")
                 + "}"
                   "})");
}

void MonacoEditor::showLineNumber(bool show) {
    m_data->exec(QStringLiteral("window.editor.updateOptions({"
                                "lineNumbers: ")
                 + (show ? "'on'" : "'off'") + "})");
}

void MonacoEditor::setRulerAt(int len) {
    QString arr;
    if (len != 0) {
        arr = QStringLiteral("%1").arg(len);
    }
    m_data->exec("window.editor.updateOptions({"
                 "rulers:["
                 + arr
                 + "]"
                   "})");
}

bool MonacoEditor::handle(const QString& path) {
    m_data->m_path = path;
    QFile file{path};
    QFileInfo info{path};
    auto result = false;
    if (info.isFile() && file.open(QFile::ReadOnly)) {
        AT_SCOPE_EXIT(file.close());
        auto content = readJS(file);
        this->setContent(content, EXT_LANG.value(info.suffix(), "txt"));
        result = true;
    } else {
        QZP_ERROR << "Could not load file at " << file.fileName();
    }
    return result;
}

QString MonacoEditor::path() const {
    return m_data->m_path;
}

bool MonacoEditor::close() {
    auto result = true;
    if (m_data->m_file.isOpen()) {
        m_data->m_file.close();
        result = !m_data->m_file.isOpen();
        if (!result) {
            QFileInfo info{m_data->m_file};
            QZP_ERROR << "Failed to close file " << info.path();
        }
    }
    return result;
}

bool MonacoEditor::save() {
    auto resp = [this](const QVariant& data) {
        auto path = m_data->m_path;
        if (!QFile::exists(path)) {
            auto path = QFileDialog::getOpenFileName(this, tr("Get file name"));
        }
        QFile file{path};
        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            AT_SCOPE_EXIT(file.close());
            auto bytes = data.toByteArray();
            auto num = file.write(bytes);
            if (num == bytes.size()) {
                m_data->m_dirty = false;
                emit this->dirtyStateChanged(false);
                emit m_data->m_qzwrapper->saved();
            } else {
                QZP_ERROR << "Failed to save file at" << path;
            }
        }
    };
    m_data->exec("window.editor.getValue()", resp);
    return true;
}

const QStringList& MonacoEditor::extension() {
    static QStringList exts;
    if (exts.isEmpty()) {
        for (auto it = EXT_LANG.cbegin(); it != EXT_LANG.cend(); ++it) {
            exts.append(it.key());
        }
    }
    return exts;
}

SharedObject::SharedObject(MonacoEditor* parent)
    : QObject(parent)
    , m_editor(parent) {
}

SharedObject::~SharedObject() {
}

void SharedObject::info(const QString& msg) {
    QZP_INFO << msg;
}

void SharedObject::error(const QString& msg) {
    QZP_ERROR << msg;
}

void SharedObject::warn(const QString& msg) {
    QZP_WARN << msg;
}

void SharedObject::dirtyChanged(bool val) {
    m_editor->m_data->m_dirty = val;
    emit m_editor->dirtyStateChanged(val);
}

void SharedObject::save() {
    m_editor->save();
}

}}} // namespace Quartz::Ext::WebTech
