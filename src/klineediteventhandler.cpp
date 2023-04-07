/*
   SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>
   SPDX-FileCopyrightText: 2023 Volker Krause <vkrause@kde.org>
   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "klineediteventhandler.h"
#include "klineediturldropeventfilter.h"

#include <QKeyEvent>
#include <QLineEdit>

class LineEditCatchReturnKey : public QObject
{
    Q_OBJECT
public:
    explicit LineEditCatchReturnKey(QObject *lineEdit);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    QLineEdit *const m_lineEdit;
};

LineEditCatchReturnKey::LineEditCatchReturnKey(QObject *lineEdit)
    : QObject(lineEdit)
    , m_lineEdit(qobject_cast<QLineEdit *>(lineEdit))
{
    m_lineEdit->installEventFilter(this);
}

bool LineEditCatchReturnKey::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_lineEdit) {
        if (event->type() == QEvent::KeyPress) {
            auto e = static_cast<QKeyEvent *>(event);
            if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) {
                const bool stopEvent = (e->modifiers() == Qt::NoButton || e->modifiers() == Qt::KeypadModifier);
                if (stopEvent) {
                    Q_EMIT m_lineEdit->returnPressed();
                }
                return true;
            }
        }
    }
    return QObject::eventFilter(obj, event);
}

void KLineEditEventHandler::catchReturnKey(QObject *lineEdit)
{
    new LineEditCatchReturnKey(lineEdit);
}

void KLineEditEventHandler::handleUrlDrops(QObject *lineEdit)
{
    auto filter = new KLineEditUrlDropEventFilter(lineEdit);
    lineEdit->installEventFilter(filter);
}

#include "klineediteventhandler.moc"
