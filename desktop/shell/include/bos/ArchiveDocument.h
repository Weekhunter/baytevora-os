#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Represents the archive document currently loaded in the Archive Manager.
 *
 * ArchiveDocument tracks archive metadata such as path, name, archive type,
 * entry count, and loaded state. It is exposed to QML through ArchiveManager.
 */
class ArchiveDocument : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString archivePath READ archivePath NOTIFY archivePathChanged FINAL)
    Q_PROPERTY(QString archiveName READ archiveName NOTIFY archiveNameChanged FINAL)
    Q_PROPERTY(QString archiveType READ archiveType NOTIFY archiveTypeChanged FINAL)
    Q_PROPERTY(int entryCount READ entryCount NOTIFY entryCountChanged FINAL)
    Q_PROPERTY(bool loaded READ loaded NOTIFY loadedChanged FINAL)
    Q_PROPERTY(QString error READ error NOTIFY errorChanged FINAL)

public:
    explicit ArchiveDocument(QObject *parent = nullptr);

    QString archivePath() const;
    QString archiveName() const;
    QString archiveType() const;
    int entryCount() const;
    bool loaded() const;
    QString error() const;

    void setArchivePath(const QString &path);
    void setArchiveName(const QString &name);
    void setArchiveType(const QString &type);
    void setEntryCount(int count);
    void setLoaded(bool loaded);
    void setError(const QString &error);

signals:
    void archivePathChanged();
    void archiveNameChanged();
    void archiveTypeChanged();
    void entryCountChanged();
    void loadedChanged();
    void errorChanged();

private:
    QString m_archivePath;
    QString m_archiveName;
    QString m_archiveType;
    int m_entryCount = 0;
    bool m_loaded = false;
    QString m_error;
};

} // namespace bos::shell
