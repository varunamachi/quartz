#pragma once

#include <memory>

class QString;
class QDomElement;

namespace Quartz {

class Theme;

class ThemeParser {
public:
    explicit ThemeParser();

    std::unique_ptr<Theme> parse(const QString& content);

private:
    bool parseDeclarations(const QDomElement& el, Theme& theme);

    bool parsePalettes(const QDomElement& el, Theme& theme);

    QString readStylesheet(const QDomElement& el, Theme& theme);

    bool parseStylesheet(const QDomElement& el, Theme& theme);
};

} // namespace Quartz
