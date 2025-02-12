/*
    This file is part of the KDE libraries
    SPDX-FileCopyrightText: 1999 Reginald Stadlbauer <reggie@kde.org>
    SPDX-FileCopyrightText: 1999 Simon Hausmann <hausmann@kde.org>
    SPDX-FileCopyrightText: 2000 Nicolas Hadacek <haadcek@kde.org>
    SPDX-FileCopyrightText: 2000 Kurt Granroth <granroth@kde.org>
    SPDX-FileCopyrightText: 2000 Michael Koch <koch@kde.org>
    SPDX-FileCopyrightText: 2001 Holger Freyther <freyther@kde.org>
    SPDX-FileCopyrightText: 2002 Ellis Whitehead <ellis@kde.org>
    SPDX-FileCopyrightText: 2003 Andras Mantia <amantia@kde.org>
    SPDX-FileCopyrightText: 2005-2006 Hamish Rodda <rodda@kde.org>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#ifndef KTOOLBARPOPUPACTION_H
#define KTOOLBARPOPUPACTION_H

#include <QToolButton>
#include <QWidgetAction>
#include <memory>

#include <kwidgetsaddons_export.h>

class QMenu;

/**
 * @class KToolBarPopupAction ktoolbarpopupaction.h KToolBarPopupAction
 *
 * This action is a normal action everywhere, except in a toolbar
 * where it also has a popupmenu (optionally delayed). This action is designed
 * for history actions (back/forward, undo/redo) and for any other action
 * that has more detail in a toolbar than in a menu (e.g. tool chooser
 * with "Other" leading to a dialog...).
 *
 * In contrast to KActionMenu, this action is a \e simple menuitem when plugged
 * into a menu, and has a popup only in a toolbar.
 *
 * Use cases include Back/Forward, and Undo/Redo. Simple click is what's most commonly
 * used, and enough for menus, but in toolbars there is \e also an optional popup
 * to go back N steps or undo N steps.
 */
class KWIDGETSADDONS_EXPORT KToolBarPopupAction : public QWidgetAction
{
    Q_OBJECT
    Q_PROPERTY(QToolButton::ToolButtonPopupMode popupMode READ popupMode WRITE setPopupMode)

public:
    // Not all constructors - because we need an icon, since this action only makes
    // sense when being plugged at least in a toolbar.
    /**
     * Create a KToolBarPopupAction, with a text, an icon, a
     * parent and a name.
     *
     * @param icon The icon to display.
     * @param text The text that will be displayed.
     * @param parent This action's parent.
     */
    KToolBarPopupAction(const QIcon &icon, const QString &text, QObject *parent);

    /**
     * Destroys the toolbar popup action.
     */
    ~KToolBarPopupAction() override;

    /**
     * The popup mode of the toolbar button.
     *
     * @see setPopupMode()
     *
     * @since 5.78
     */
    QToolButton::ToolButtonPopupMode popupMode() const;

    /**
     * Determines the popup mode of the toolbar button.
     *
     * Options are:
     *  - QToolButton::InstantPopup
     *    Clicking anywhere on the toolbar button opens the popup menu.
     *  - QToolButton::DelayedPopup
     *    Clicking anywhere on the toolbar button triggers the default action.
     *    Clicking and holding the toolbar button opens the popup menu instead.
     *  - QToolButton::MenuButtonPopup (Default)
     *    The toolbar button is split in a main button (triggers default action)
     *    and an arrow button (opens the popup menu).
     *
     * @see QToolButton
     *
     * @since 5.78
     */
    void setPopupMode(QToolButton::ToolButtonPopupMode popupMode);

    /**
     * Reimplemented from QWidgetAction.
     */
    QWidget *createWidget(QWidget *parent) override;

private:
    std::unique_ptr<class KToolBarPopupActionPrivate> const d;
};

#endif
