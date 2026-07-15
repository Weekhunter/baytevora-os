#pragma once

#include <QKeySequence>
#include <QObject>
#include <QString>

#include "bos/ShortcutContext.h"

class QShortcut;

namespace bos::shell {

/**
 * @brief Represents one registered keyboard shortcut.
 *
 * Shortcut stores the metadata and owns the native QShortcut object used to
 * receive key events. Enabling/disabling the shortcut updates the underlying
 * QShortcut so inactive shortcuts are ignored by Qt.
 */
class Shortcut : public QObject {
    Q_OBJECT

    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString keySequence READ keySequence CONSTANT)
    Q_PROPERTY(bos::shell::ShortcutContext context READ context CONSTANT)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QString description READ description CONSTANT)

public:
    explicit Shortcut(int id, const QString &name, const QKeySequence &keySequence,
                      ShortcutContext context, const QString &description,
                      QWidget *shortcutParent, QObject *parent = nullptr);
    ~Shortcut() override;

    int id() const;
    QString name() const;
    QString keySequence() const;
    ShortcutContext context() const;
    bool enabled() const;
    QString description() const;

    void setEnabled(bool enabled);

    QShortcut *nativeShortcut() const;

signals:
    void enabledChanged();
    void triggered(int id);

private:
    int m_id;
    QString m_name;
    QKeySequence m_keySequence;
    ShortcutContext m_context;
    bool m_enabled = true;
    QString m_description;
    QShortcut *m_nativeShortcut = nullptr;
};

} // namespace bos::shell
