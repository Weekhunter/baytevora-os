#include "bldf/ApplicationRegistrar.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

namespace bldf {

ApplicationRegistrar::ApplicationRegistrar(QObject *parent)
    : QObject(parent)
{
}

QString ApplicationRegistrar::targetRoot() const { return m_targetRoot; }
void ApplicationRegistrar::setTargetRoot(const QString &value)
{
    if (m_targetRoot == value) return;
    m_targetRoot = value;
    emit targetRootChanged();
}

QString ApplicationRegistrar::sourceRoot() const { return m_sourceRoot; }
void ApplicationRegistrar::setSourceRoot(const QString &value)
{
    if (m_sourceRoot == value) return;
    m_sourceRoot = value;
    emit sourceRootChanged();
}

bool ApplicationRegistrar::registerAll()
{
    if (m_targetRoot.isEmpty()) {
        emit logError(QStringLiteral("targetRoot is not set."));
        return false;
    }

    const struct App {
        QString name;
        QString exec;
        QString icon;
        QString comment;
    } apps[] = {
        { QStringLiteral("PDF Studio"), QStringLiteral("baytevora-pdf-studio"), QStringLiteral("baytevora-pdf"), QStringLiteral("View and edit PDF documents") },
        { QStringLiteral("Browser"), QStringLiteral("baytevora-browser"), QStringLiteral("baytevora-browser"), QStringLiteral("Browse the web") },
        { QStringLiteral("Store"), QStringLiteral("baytevora-store"), QStringLiteral("baytevora-store"), QStringLiteral("Browse and install applications") },
        { QStringLiteral("Settings"), QStringLiteral("baytevora-settings"), QStringLiteral("baytevora-settings"), QStringLiteral("System settings") },
        { QStringLiteral("Welcome Center"), QStringLiteral("baytevora-welcome"), QStringLiteral("baytevora-welcome"), QStringLiteral("Get started with Baytevora OS") }
    };

    for (const auto &app : apps) {
        if (!registerApplication(app.name, app.exec, app.icon, app.comment)) return false;
    }

    if (!configureMimeTypes()) return false;
    if (!updateIconCache()) return false;
    emit logInfo(QStringLiteral("All applications registered."));
    return true;
}

bool ApplicationRegistrar::registerApplication(const QString &name, const QString &exec,
                                                const QString &icon, const QString &comment)
{
    const QString appsDir = m_targetRoot + QStringLiteral("/usr/share/applications");
    QDir().mkpath(appsDir);
    const QString id = exec.toLower().replace(QLatin1Char(' '), QLatin1Char('-'));
    const QString path = appsDir + QStringLiteral("/") + id + QStringLiteral(".desktop");

    const QString contents = QStringLiteral(
        "[Desktop Entry]\n"
        "Name=%1\n"
        "Comment=%2\n"
        "Exec=%3 %U\n"
        "Icon=%4\n"
        "Type=Application\n"
        "Terminal=false\n"
        "Categories=System;Baytevora;\n"
        "MimeType=application/x-baytevora;\n"
    ).arg(name, comment.isEmpty() ? name : comment, exec, icon);

    if (!writeFile(path, contents)) return false;
    emit logInfo(QStringLiteral("Registered %1").arg(name));
    return true;
}

bool ApplicationRegistrar::configureMimeTypes()
{
    const QString mimeDir = m_targetRoot + QStringLiteral("/usr/share/mime/packages");
    QDir().mkpath(mimeDir);
    const QString path = mimeDir + QStringLiteral("/baytevora.xml");
    const QString contents = QStringLiteral(
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<mime-info xmlns=\"http://www.freedesktop.org/standards/shared-mime-info\">\n"
        "  <mime-type type=\"application/x-baytevora\">\n"
        "    <comment>Baytevora application resource</comment>\n"
        "    <glob pattern=\"*.btr\"/>\n"
        "  </mime-type>\n"
        "</mime-info>\n"
    );
    if (!writeFile(path, contents)) return false;

    // Associate the generic Baytevora mime type with the applications.
    const QString mimeInfoDir = m_targetRoot + QStringLiteral("/usr/share/applications");
    QDir().mkpath(mimeInfoDir);
    const QString cachePath = mimeInfoDir + QStringLiteral("/mimeinfo.cache");
    QFile cache(cachePath);
    if (cache.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream s(&cache);
        s << "application/x-baytevora=baytevora-pdf-studio.desktop;baytevora-browser.desktop;baytevora-store.desktop;baytevora-settings.desktop;baytevora-welcome.desktop;\n";
    }
    emit logInfo(QStringLiteral("MIME types configured."));
    return true;
}

bool ApplicationRegistrar::updateIconCache()
{
    const QString iconsDir = m_targetRoot + QStringLiteral("/usr/share/icons/baytevora");
    QDir().mkpath(iconsDir);
    // Placeholder icon files are fine for Alpha.
    const QStringList names = {
        QStringLiteral("baytevora-pdf"), QStringLiteral("baytevora-browser"),
        QStringLiteral("baytevora-store"), QStringLiteral("baytevora-settings"),
        QStringLiteral("baytevora-welcome")
    };
    for (const QString &name : names) {
        const QString iconPath = iconsDir + QStringLiteral("/") + name + QStringLiteral(".png");
        QFile icon(iconPath);
        if (icon.open(QIODevice::WriteOnly)) icon.write("# placeholder icon\n");
    }
    emit logInfo(QStringLiteral("Icon placeholders created."));
    return true;
}

bool ApplicationRegistrar::writeFile(const QString &path, const QString &contents)
{
    QDir().mkpath(QFileInfo(path).absolutePath());
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        emit logError(QStringLiteral("Failed to write %1").arg(path));
        return false;
    }
    QTextStream stream(&file);
    stream << contents;
    return true;
}

} // namespace bldf
