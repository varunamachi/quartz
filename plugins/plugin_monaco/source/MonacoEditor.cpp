#include <QWebEngineView>
#include <QVBoxLayout>
#include <QFile>
#include <QWebChannel>
#include <QThread>
#include <QFileInfo>
#include <QQueue>

#include <plugin_base/PluginLogging.h>
#include <plugin_base/PluginContext.h>

#include "MonacoEditor.h"


#define EXEC(statement)                                                 \
    if (!m_data->m_initialized) {                                       \
        m_data->m_pendingCommands.append([=]() {                        \
            m_data->m_monaco->page()->runJavaScript(statement);         \
        });                                                             \
    } else {                                                            \
        m_data->m_monaco->page()->runJavaScript(statement);             \
    }                                                                   \

namespace Quartz {

const QHash<QString, QString> EXT_LANG = {
    { "",                   "plaintext" },
    { "conf",               "plaintext" },
    { "config",             "plaintext" },
    { "txt",                "plaintext" },
    { "gitignore",          "plaintext" },
    { "cmake",              "cmake" },
    { "json",               "json" },
    { "bowerrc",            "json" },
    { "jshintrc",           "json" },
    { "jscsrc",             "json" },
    { "eslintrc",           "json" },
    { "babelrc",            "json" },
    { "bat",                "bat" },
    { "cmd",                "bat" },
    { "coffee",             "coffeescript" },
    { "c",                  "c" },
    { "h",                  "c" },
    { "cpp",                "cpp" },
    { "cc",                 "cpp" },
    { "cxx",                "cpp" },
    { "hpp",                "cpp" },
    { "hh",                 "cpp" },
    { "hxx",                "cpp" },
    { "cs",                 "csharp" },
    { "csx",                "csharp" },
    { "cake",               "csharp" },
    { "css",                "css" },
    { "dockerfile",         "dockerfile" },
    { "dart",               "dart" },
    { "fs",                 "fsharp" },
    { "fsi",                "fsharp" },
    { "ml",                 "fsharp" },
    { "mli",                "fsharp" },
    { "fsx",                "fsharp" },
    { "fsscript",           "fsharp" },
    { "go",                 "go" },
    { "handlebars",         "handlebars" },
    { "hbs",                "handlebars" },
    { "html",               "html" },
    { "htm",                "html" },
    { "shtml",              "html" },
    { "xhtml",              "html" },
    { "mdoc",               "html" },
    { "jsp",                "html" },
    { "asp",                "html" },
    { "aspx",               "html" },
    { "jshtm",              "html" },
    { "ini",                "ini" },
    { "properties",         "ini" },
    { "gitconfig",          "ini" },
    { "java",               "java" },
    { "jav",                "java" },
    { "js",                 "javascript" },
    { "es6",                "javascript" },
    { "jsx",                "javascript" },
    { "less",               "less" },
    { "lua",                "lua" },
    { "md",                 "markdown" },
    { "markdown",           "markdown" },
    { "mdown",              "markdown" },
    { "mkdn",               "markdown" },
    { "mkd",                "markdown" },
    { "mdwn",               "markdown" },
    { "mdtxt",              "markdown" },
    { "mdtext",             "markdown" },
    { "dax",                "msdax" },
    { "msdax",              "msdax" },
    { "m",                  "objective-c" },
    { "php",                "php" },
    { "php4",               "php" },
    { "php5",               "php" },
    { "phtml",              "php" },
    { "ctp",                "php" },
    { "dats",               "postiats" },
    { "sats",               "postiats" },
    { "hats",               "postiats" },
    { "pq",                 "powerquery" },
    { "pqm",                "powerquery" },
    { "ps1",                "powershell" },
    { "psm1",               "powershell" },
    { "psd1",               "powershell" },
    { "jade",               "pug" },
    { "pug",                "pug" },
    { "py",                 "python" },
    { "rpy",                "python" },
    { "pyw",                "python" },
    { "cpy",                "python" },
    { "gyp",                "python" },
    { "gypi",               "python" },
    { "r",                  "r" },
    { "rhistory",           "r" },
    { "rprofile",           "r" },
    { "rt",                 "r" },
    { "cshtml",             "razor" },
    { "redis",              "redis" },
    { "rb",                 "ruby" },
    { "rbx",                "ruby" },
    { "rjs",                "ruby" },
    { "gemspec",            "ruby" },
    { "pp",                 "ruby" },
    { "rs",                 "rust" },
    { "rlib",               "rust" },
    { "sb",                 "sb" },
    { "scss",               "scss" },
    { "sol",                "sol" },
    { "sql",                "sql" },
    { "st",                 "st" },
    { "iecst",              "st" },
    { "iecplc",             "st" },
    { "lc3lib",             "st" },
    { "swift",              "swift" },
    { "ts",                 "typescript" },
    { "tsx",                "typescript" },
    { "vb",                 "vb" },
    { "xml",                "xml" },
    { "dtd",                "xml" },
    { "ascx",               "xml" },
    { "csproj",             "xml" },
    { "config",             "xml" },
    { "wxi",                "xml" },
    { "wxl",                "xml" },
    { "wxs",                "xml" },
    { "xaml",               "xml" },
    { "svg",                "xml" },
    { "svgz",               "xml" },
    { "yaml",               "yaml" },
    { "yml",                "yaml" },
    { "scm",                "scheme" },
    { "ss",                 "scheme" },
    { "sch",                "scheme" },
    { "rkt",                "scheme" },
    { "clj",                "clojure" },
    { "clojure",            "clojure" },
    { "sh",                 "shell" },
    { "bash",               "shell" },
    { "pl",                 "perl" },
    { "azcli",              "azcli" },
    { "cls",                "apex" },
};


QString readJS(QFile &file) {
    QString content;
    content.reserve(static_cast<int>(file.size()));
    QTextStream stream{&file};
    while (!stream.atEnd()) {
        auto line = stream.readLine();
        for (int i = 0; i < line.size(); ++ i) {
            switch (line.at(i).toLatin1()) {
            case '\\': content.append("\\\\"); break;
            case '`' : content.append("\\`");  break;
            case '\"': content.append("\\\""); break;
            case '$' : content.append("\\$");  break;
            default: content.append(line.at(i)); break;
            }
        }
        content.append("\\n");
    }
    return content;
}

struct MonacoEditor::Data
{
    explicit Data(QWidget *parent)
        : m_monaco(new QWebEngineView(parent))
        , m_qzwrapper(new SharedObject(parent))
        , m_initialized(false)
    {
        auto channel = new QWebChannel(parent);
        m_monaco->page()->setWebChannel(channel);
        channel->registerObject(QStringLiteral("qzwrapper"), m_qzwrapper);
    }

    QWebEngineView *m_monaco;

    SharedObject *m_qzwrapper;

    bool m_initialized;

    QString m_path;

    QFile m_file;

    QQueue<std::function<void()>> m_pendingCommands;

    static QStringList s_extensions;
};


MonacoEditor::MonacoEditor(QWidget *parent)
    : AbstractFileHandler(parent)
    , m_data(std::make_unique<Data>(this))
{
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

    connect(m_data->m_monaco,
            &QWebEngineView::loadFinished,
            [this]() {
        m_data->m_initialized = true;
        while (!m_data->m_pendingCommands.empty()) {
            auto func = m_data->m_pendingCommands.takeFirst();
            func();
        }
    });
}

MonacoEditor::~MonacoEditor()
{

}

SharedObject *MonacoEditor::controller() const
{
    return  m_data->m_qzwrapper;
}

void MonacoEditor::setContent(const QString &ct, const QString &lang)
{
//    auto  ct = content;
//    ct.replace(QChar('\\'), QStringLiteral("\\\\"));
//    ct.replace(QChar('`'), QStringLiteral("\\`"));
//    ct.replace(QChar('\"'), QStringLiteral("\\\""));
    EXEC(
        "if (window.editor) {"
            "window.editor.setValue(`"+ct+"`);"
            "monaco.editor.setModelLanguage("
                "window.editor.getModel(), "
                "`" + lang+ "`);"
         "}"
    );
}

void MonacoEditor::setLanguage(const QString &language)
{
    EXEC(
        "if (window.editor) {"
            " monaco.editor.setModelLanguage("
                "window.editor.getModel(), "
                "`" + language + "`);"
        "}"
    );
}

void MonacoEditor::setTheme(const QString &theme)
{
    EXEC(
        "if (window.editor) {"
            " monaco.editor.setTheme("
                "window.editor.getModel(), "
                "`" + theme + "`);"
        "}"
    );
}

void MonacoEditor::setMinimapState(bool show)
{
    EXEC(
         "if (window.editor) {"
//                " monaco.editor.setTheme("
//                "window.editor.getModel(), "
//                "`" + theme + "`);"
         "}"
                );
}

void MonacoEditor::mapToLanguage(const QFileInfo &info)
{

}

bool MonacoEditor::handle(const QString &path)
{
    m_data->m_path = path;
    QFile file{path};
    QFileInfo info{path};
    auto result = false;
    if ( info.isFile() && file.open(QFile::ReadOnly)) {
//        auto content = file.readAll();
        auto content = readJS(file);
        this->setContent(content, EXT_LANG.value(info.suffix(), "txt"));
        file.close();
        result = true;
    } else {
        QZP_ERROR << "Could not load file at " << file.fileName();
    }
    return result;
}

QString MonacoEditor::path() const
{
    return m_data->m_path;
}

bool MonacoEditor::close()
{
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

bool MonacoEditor::save()
{
    return false;
}

const QStringList &MonacoEditor::extension()
{
    static QStringList exts;
    if (exts.isEmpty()) {
        for (auto it = EXT_LANG.cbegin(); it != EXT_LANG.cend(); ++ it) {
            exts.append(it.key());
        }
    }
    return exts;
}





SharedObject::SharedObject(QObject *parent)
    : QObject (parent)
{

}

SharedObject::~SharedObject()
{

}

void SharedObject::print(const QString &msg)
{
    QZP_INFO << msg;
}

}

