#include "bos/ApplicationManager.h"

#include <QDebug>

#include "bos/ApplicationInfo.h"
#include "bos/ApplicationLauncher.h"
#include "bos/ApplicationRegistry.h"
#include "bos/ArchiveApplication.h"
#include "bos/BrowserApplication.h"
#include "bos/CalculatorApplication.h"
#include "bos/FileManagerApplication.h"
#include "bos/MediaPlayerApplication.h"
#include "bos/NetworkApplication.h"
#include "bos/PdfStudioApplication.h"
#include "bos/PrintApplication.h"
#include "bos/StorageApplication.h"
#include "bos/SystemMonitorApplication.h"
#include "bos/TaskManagerApplication.h"
#include "bos/TextEditorApplication.h"
#include "bos/ImageViewerApplication.h"
#include "bos/NotesApplication.h"
#include "bos/NotificationManager.h"
#include "bos/PackageManagerApplication.h"
#include "bos/SettingsApplication.h"
#include "bos/StoreApplication.h"
#include "bos/TerminalApplication.h"
#include "bos/WindowManager.h"

namespace bos::shell {

ApplicationManager::ApplicationManager(QObject *parent)
    : QObject(parent)
    , m_registry(std::make_unique<ApplicationRegistry>())
    , m_launcher(std::make_unique<ApplicationLauncher>(m_registry.get()))
{
}

ApplicationManager::~ApplicationManager() = default;

QString ApplicationManager::name() const
{
    return QStringLiteral("ApplicationManager");
}

void ApplicationManager::initialize()
{
    qDebug() << QStringLiteral("[BDE] ApplicationManager initialized");
    registerPlaceholderApplications();
}

void ApplicationManager::start()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("started");
}

void ApplicationManager::shutdown()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("shutting down");
}

void ApplicationManager::setWindowManager(WindowManager *windowManager)
{
    if (m_windowManager == windowManager) {
        return;
    }

    if (m_windowManager) {
        disconnect(m_windowManager, nullptr, this, nullptr);
    }

    m_windowManager = windowManager;

    if (m_windowManager) {
        connect(m_windowManager,
                &WindowManager::windowClosed,
                this,
                &ApplicationManager::onWindowClosed);
    }
}

void ApplicationManager::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

void ApplicationManager::setFileManagerApplication(FileManagerApplication *fileManager)
{
    m_fileManagerApplication = fileManager;
}

void ApplicationManager::setSettingsApplication(SettingsApplication *settings)
{
    m_settingsApplication = settings;
}

void ApplicationManager::setTerminalApplication(TerminalApplication *terminal)
{
    m_terminalApplication = terminal;
}

void ApplicationManager::setStoreApplication(StoreApplication *store)
{
    m_storeApplication = store;
}

void ApplicationManager::setPackageManagerApplication(PackageManagerApplication *packageManager)
{
    m_packageManagerApplication = packageManager;
}

void ApplicationManager::setBrowserApplication(BrowserApplication *browser)
{
    m_browserApplication = browser;
}

void ApplicationManager::setNotesApplication(NotesApplication *notes)
{
    m_notesApplication = notes;
}

void ApplicationManager::setImageViewerApplication(ImageViewerApplication *imageViewer)
{
    m_imageViewerApplication = imageViewer;
}

void ApplicationManager::setCalculatorApplication(CalculatorApplication *calculator)
{
    m_calculatorApplication = calculator;
}

void ApplicationManager::setPdfStudioApplication(PdfStudioApplication *pdfStudio)
{
    m_pdfStudioApplication = pdfStudio;
}

void ApplicationManager::setArchiveApplication(ArchiveApplication *archive)
{
    m_archiveApplication = archive;
}

void ApplicationManager::setMediaPlayerApplication(MediaPlayerApplication *mediaPlayer)
{
    m_mediaPlayerApplication = mediaPlayer;
}

void ApplicationManager::setTextEditorApplication(TextEditorApplication *textEditor)
{
    m_textEditorApplication = textEditor;
}

void ApplicationManager::setSystemMonitorApplication(SystemMonitorApplication *systemMonitor)
{
    m_systemMonitorApplication = systemMonitor;
}

void ApplicationManager::setTaskManagerApplication(TaskManagerApplication *taskManager)
{
    m_taskManagerApplication = taskManager;
}

void ApplicationManager::setNetworkApplication(NetworkApplication *networkApplication)
{
    m_networkApplication = networkApplication;
}

void ApplicationManager::setStorageApplication(StorageApplication *storageApplication)
{
    m_storageApplication = storageApplication;
}

void ApplicationManager::setPrintApplication(PrintApplication *printApplication)
{
    m_printApplication = printApplication;
}

SettingsApplication *ApplicationManager::settingsApplication() const
{
    return m_settingsApplication;
}

QVariantList ApplicationManager::applications() const
{
    QVariantList list;
    for (const auto &info : m_registry->applications()) {
        list.append(info.toMap());
    }
    return list;
}

QVariantList ApplicationManager::runningApplications() const
{
    QVariantList list;
    for (const auto &name : m_running) {
        list.append(name);
    }
    return list;
}

bool ApplicationManager::launchApplication(const QString &name)
{
    qDebug() << QStringLiteral("[BDE] Launch request:") << name;

    if (!m_launcher->canLaunch(name)) {
        qWarning() << QStringLiteral("[BDE] Launch validation failed:") << m_launcher->lastError();
        return false;
    }

    const ApplicationInfo *info = m_registry->findByName(name);
    if (!info) {
        qWarning() << QStringLiteral("[BDE] Application not found:") << name;
        return false;
    }

    if (info->singleInstance() && m_running.contains(name)) {
        qDebug() << QStringLiteral("[BDE] Launch denied:") << name << QStringLiteral("already running");
        return false;
    }

    qDebug() << QStringLiteral("[BDE] Launch approved");

    if (!m_windowManager) {
        qWarning() << QStringLiteral("[BDE] WindowManager not available; cannot create window for") << name;
        return false;
    }

    int windowId = -1;

    // Sprint 12/13: File Manager and Settings are real applications and use
    // dedicated handlers. All other applications continue to use a demo window.
    if (name == QStringLiteral("File Manager") && m_fileManagerApplication) {
        windowId = m_fileManagerApplication->open();
        if (windowId < 0) {
            qWarning() << QStringLiteral("[BDE] Failed to open File Manager");
            return false;
        }
    } else if (name == QStringLiteral("Settings") && m_settingsApplication) {
        windowId = m_settingsApplication->open();
        if (windowId < 0) {
            qWarning() << QStringLiteral("[BDE] Failed to open Settings");
            return false;
        }
    } else if (name == QStringLiteral("Terminal") && m_terminalApplication) {
        windowId = m_terminalApplication->open();
        if (windowId < 0) {
            qWarning() << QStringLiteral("[BDE] Failed to open Terminal");
            return false;
        }
    } else if (name == QStringLiteral("Baytevora Store") && m_storeApplication) {
        windowId = m_storeApplication->open();
        if (windowId < 0) {
            qWarning() << QStringLiteral("[BDE] Failed to open Baytevora Store");
            return false;
        }
    } else if (name == QStringLiteral("Package Manager") && m_packageManagerApplication) {
        windowId = m_packageManagerApplication->open();
        if (windowId < 0) {
            qWarning() << QStringLiteral("[BDE] Failed to open Package Manager");
            return false;
        }
    } else if (name == QStringLiteral("Browser") && m_browserApplication) {
        windowId = m_browserApplication->open();
        if (windowId < 0) {
            qWarning() << QStringLiteral("[BDE] Failed to open Browser");
            return false;
        }
    } else if (name == QStringLiteral("Notes") && m_notesApplication) {
        windowId = m_notesApplication->open();
        if (windowId < 0) {
            qWarning() << QStringLiteral("[BDE] Failed to open Notes");
            return false;
        }
    } else if (name == QStringLiteral("Image Viewer") && m_imageViewerApplication) {
        windowId = m_imageViewerApplication->open();
        if (windowId < 0) {
            qWarning() << QStringLiteral("[BDE] Failed to open Image Viewer");
            return false;
        }
    } else if (name == QStringLiteral("Calculator") && m_calculatorApplication) {
        windowId = m_calculatorApplication->open();
        if (windowId < 0) {
            qWarning() << QStringLiteral("[BDE] Failed to open Calculator");
            return false;
        }
    } else if (name == QStringLiteral("Baytevora PDF Studio") && m_pdfStudioApplication) {
        windowId = m_pdfStudioApplication->open();
        if (windowId < 0) {
            qWarning() << QStringLiteral("[BDE] Failed to open Baytevora PDF Studio");
            return false;
        }
    } else if (name == QStringLiteral("Archive Manager") && m_archiveApplication) {
        windowId = m_archiveApplication->open();
        if (windowId < 0) {
            qWarning() << QStringLiteral("[BDE] Failed to open Archive Manager");
            return false;
        }
    } else if (name == QStringLiteral("Media Player") && m_mediaPlayerApplication) {
        windowId = m_mediaPlayerApplication->open();
        if (windowId < 0) {
            qWarning() << QStringLiteral("[BDE] Failed to open Media Player");
            return false;
        }
    } else if (name == QStringLiteral("Text Editor") && m_textEditorApplication) {
        windowId = m_textEditorApplication->open();
        if (windowId < 0) {
            qWarning() << QStringLiteral("[BDE] Failed to open Text Editor");
            return false;
        }
    } else if (name == QStringLiteral("System Monitor") && m_systemMonitorApplication) {
        windowId = m_systemMonitorApplication->open();
        if (windowId < 0) {
            qWarning() << QStringLiteral("[BDE] Failed to open System Monitor");
            return false;
        }
    } else if (name == QStringLiteral("Task Manager") && m_taskManagerApplication) {
        windowId = m_taskManagerApplication->open();
        if (windowId < 0) {
            qWarning() << QStringLiteral("[BDE] Failed to open Task Manager");
            return false;
        }
    } else if (name == QStringLiteral("Network Manager") && m_networkApplication) {
        windowId = m_networkApplication->open();
        if (windowId < 0) {
            qWarning() << QStringLiteral("[BDE] Failed to open Network Manager");
            return false;
        }
    } else if (name == QStringLiteral("Storage Manager") && m_storageApplication) {
        windowId = m_storageApplication->open();
        if (windowId < 0) {
            qWarning() << QStringLiteral("[BDE] Failed to open Storage Manager");
            return false;
        }
    } else if (name == QStringLiteral("Print Manager") && m_printApplication) {
        windowId = m_printApplication->open();
        if (windowId < 0) {
            qWarning() << QStringLiteral("[BDE] Failed to open Print Manager");
            return false;
        }
    } else {
        windowId = m_windowManager->createApplicationWindow(info->name());
        if (windowId < 0) {
            qWarning() << QStringLiteral("[BDE] Failed to create window for") << name;
            return false;
        }
        qDebug() << QStringLiteral("[BDE] Demo window created:") << info->name();

        if (m_notificationManager) {
            m_notificationManager->createNotification(
                QStringLiteral("Application Started"),
                name + QStringLiteral(" launched successfully."),
                name,
                QStringLiteral("success"));
        }
    }

    m_running.insert(name);
    m_windowToApp.insert(windowId, name);
    emit runningApplicationsChanged();

    return true;
}

bool ApplicationManager::openFileWithApplication(const QString &name, const QString &filePath)
{
    int windowId = -1;

    if (name == QStringLiteral("Notes") && m_notesApplication) {
        windowId = m_notesApplication->openFile(filePath);
    } else if (name == QStringLiteral("Image Viewer") && m_imageViewerApplication) {
        windowId = m_imageViewerApplication->openFile(filePath);
    } else if (name == QStringLiteral("Baytevora PDF Studio") && m_pdfStudioApplication) {
        windowId = m_pdfStudioApplication->openFile(filePath);
    } else if (name == QStringLiteral("Archive Manager") && m_archiveApplication) {
        windowId = m_archiveApplication->openFile(filePath);
    }

    if (windowId < 0) {
        qWarning() << QStringLiteral("[BDE] Failed to open") << name << QStringLiteral("with file") << filePath;
        return false;
    }

    m_running.insert(name);
    m_windowToApp.insert(windowId, name);
    emit runningApplicationsChanged();

    if (m_notificationManager) {
        m_notificationManager->createNotification(
            QStringLiteral("Application Started"),
            name + QStringLiteral(" opened ") + filePath,
            name,
            QStringLiteral("success"));
    }
    return true;
}

void ApplicationManager::registerPlaceholderApplications()
{
    struct Placeholder {
        QString id;
        QString name;
        QString description;
        QString category;
        QString iconName;
        bool singleInstance;
    };

    // Milestone E: iconName now maps to the official product name so the
    // BrandingManager can resolve the correct symbol or logo.
    const std::vector<Placeholder> placeholders = {
        {QStringLiteral("file-manager"), QStringLiteral("File Manager"), QStringLiteral("Browse files"), QStringLiteral("Utilities"), QStringLiteral("File Manager"), false},
        {QStringLiteral("terminal"), QStringLiteral("Terminal"), QStringLiteral("Command line"), QStringLiteral("Utilities"), QStringLiteral("Terminal"), false},
        {QStringLiteral("settings"), QStringLiteral("Settings"), QStringLiteral("System settings"), QStringLiteral("System"), QStringLiteral("Settings"), false},
        {QStringLiteral("browser"), QStringLiteral("Browser"), QStringLiteral("Web browser"), QStringLiteral("Internet"), QStringLiteral("Browser"), false},
        {QStringLiteral("calculator"), QStringLiteral("Calculator"), QStringLiteral("Basic calculator"), QStringLiteral("Utilities"), QStringLiteral("Calculator"), false},
        {QStringLiteral("notes"), QStringLiteral("Notes"), QStringLiteral("Take and manage notes"), QStringLiteral("Productivity"), QStringLiteral("Notes"), false},
        {QStringLiteral("image-viewer"), QStringLiteral("Image Viewer"), QStringLiteral("View images"), QStringLiteral("Media"), QStringLiteral("Image Viewer"), false},
        {QStringLiteral("pdf-studio"), QStringLiteral("Baytevora PDF Studio"), QStringLiteral("View, annotate, and print PDF documents"), QStringLiteral("Productivity"), QStringLiteral("Baytevora PDF Studio"), false},
        {QStringLiteral("archive-manager"), QStringLiteral("Archive Manager"), QStringLiteral("Inspect archive files"), QStringLiteral("Utilities"), QStringLiteral("Archive Manager"), false},
        {QStringLiteral("media-player"), QStringLiteral("Media Player"), QStringLiteral("Play media files"), QStringLiteral("Media"), QStringLiteral("Media Player"), false},
        {QStringLiteral("text-editor"), QStringLiteral("Text Editor"), QStringLiteral("Edit text files"), QStringLiteral("Productivity"), QStringLiteral("Text Editor"), false},
        {QStringLiteral("system-monitor"), QStringLiteral("System Monitor"), QStringLiteral("View system metrics"), QStringLiteral("System"), QStringLiteral("System Monitor"), false},
        {QStringLiteral("task-manager"), QStringLiteral("Task Manager"), QStringLiteral("Manage running tasks"), QStringLiteral("System"), QStringLiteral("Task Manager"), false},
        {QStringLiteral("network-manager"), QStringLiteral("Network Manager"), QStringLiteral("Manage network connections"), QStringLiteral("System"), QStringLiteral("Network Manager"), false},
        {QStringLiteral("storage-manager"), QStringLiteral("Storage Manager"), QStringLiteral("View storage devices"), QStringLiteral("System"), QStringLiteral("Storage Manager"), false},
        {QStringLiteral("print-manager"), QStringLiteral("Print Manager"), QStringLiteral("Manage printers and print jobs"), QStringLiteral("System"), QStringLiteral("Print Manager"), false},
        {QStringLiteral("store"), QStringLiteral("Baytevora Store"), QStringLiteral("Discover and install applications"), QStringLiteral("System"), QStringLiteral("Store"), false},
        {QStringLiteral("package-manager"), QStringLiteral("Package Manager"), QStringLiteral("Manage packages, repositories, and transactions"), QStringLiteral("System"), QStringLiteral("Store"), false},
        {QStringLiteral("browser"), QStringLiteral("Browser"), QStringLiteral("Browse the web"), QStringLiteral("System"), QStringLiteral("Browser"), false}
    };

    for (const auto &placeholder : placeholders) {
        m_registry->registerApplication(ApplicationInfo(
            placeholder.id,
            placeholder.name,
            placeholder.description,
            QStringLiteral("1.0.0"),
            placeholder.category,
            placeholder.iconName,
            QStringLiteral("/usr/bin/") + placeholder.id,
            placeholder.singleInstance));

        qDebug() << QStringLiteral("[BDE] Application registered:") << placeholder.name;
    }

    emit applicationsChanged();
}

void ApplicationManager::onWindowClosed(int id)
{
    auto it = m_windowToApp.find(id);
    if (it == m_windowToApp.end()) {
        return;
    }

    const QString appName = it.value();
    m_windowToApp.erase(it);

    // Only remove from running set if no other window is open for this app.
    if (!m_windowToApp.values().contains(appName)) {
        m_running.remove(appName);
        emit runningApplicationsChanged();
    }
}

} // namespace bos::shell
