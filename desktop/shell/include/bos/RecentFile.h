#pragma once

#include <QDateTime>
#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Represents a recently opened file entry.
 */
class RecentFile : public QObject {
    Q_OBJECT

    Q_PROPERTY(int recentId READ recentId NOTIFY recentIdChanged FINAL)
    Q_PROPERTY(QString fileName READ fileName NOTIFY fileNameChanged FINAL)
    Q_PROPERTY(QString path READ path NOTIFY pathChanged FINAL)
    Q_PROPERTY(QString fileType READ fileType NOTIFY fileTypeChanged FINAL)
    Q_PROPERTY(QDateTime lastOpened READ lastOpened NOTIFY lastOpenedChanged FINAL)

public:
    explicit RecentFile(int recentId, QObject *parent = nullptr);
    ~RecentFile() override;

    int recentId() const;
    QString fileName() const;
    QString path() const;
    QString fileType() const;
    QDateTime lastOpened() const;

    void setFileName(const QString &fileName);
    void setPath(const QString &path);
    void setFileType(const QString &fileType);
    void setLastOpened(const QDateTime &lastOpened);

signals:
    void recentIdChanged();
    void fileNameChanged();
    void pathChanged();
    void fileTypeChanged();
    void lastOpenedChanged();

private:
    int m_recentId = -1;
    QString m_fileName;
    QString m_path;
    QString m_fileType;
    QDateTime m_lastOpened;
};

} // namespace bos::shell
