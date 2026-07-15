#pragma once

#include <QObject>
#include <QString>
#include <QStringList>

namespace big {

/**
 * @brief Centralized timestamped logging for the ISO build process.
 */
class BuildLogger : public QObject {
    Q_OBJECT

public:
    explicit BuildLogger(QObject *parent = nullptr);

    void logInfo(const QString &message);
    void logWarning(const QString &message);
    void logError(const QString &message);

    QStringList logs() const;
    QString getLogs() const;
    bool saveToFile(const QString &path) const;

signals:
    void logAdded(const QString &entry);

private:
    QString formatLine(const QString &level, const QString &message) const;

    QStringList m_logs;
};

} // namespace big
