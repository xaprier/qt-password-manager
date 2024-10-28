#include "MultiSelectionBox.hpp"

#include <qlineedit.h>

#include "Application.hpp"
#include "ClickableLineEdit.hpp"
#include "MultiSelectionMenu.hpp"

MultiSelectionBox::MultiSelectionBox(QWidget *parent) : QComboBox(parent), m_menu(new MultiSelectionMenu) {
    auto *lineEdit = new ClickableLineEdit(this);
    setLineEdit(lineEdit);
    setEditable(true);
    lineEdit->setReadOnly(true);

    // we should connect lineEdit click to showPopup also
    connect(lineEdit, &ClickableLineEdit::clicked, this, [&]() {
        showPopup();
    });
}

MultiSelectionBox::~MultiSelectionBox() {
}

void MultiSelectionBox::AddItem(const QString &text, const QString &path) {
    auto *action = new QAction(text, this);
    action->setCheckable(true);
    action->setToolTip(path);
    action->setIcon(QApplication::style()->standardIcon(QStyle::SP_FileIcon));
    connect(action, &QAction::toggled, this, &MultiSelectionBox::sl_UpdateText);
    m_menu->addAction(action);
}

QStringList MultiSelectionBox::SelectedItems() const {
    QStringList selected;
    for (QAction *action : m_menu->actions()) {
        if (action->isChecked()) {
            selected << action->toolTip();
        }
    }
    return selected;
}

QStringList MultiSelectionBox::SelectedItemNames() const {
    QStringList selected;
    for (QAction *action : m_menu->actions()) {
        if (action->isChecked()) {
            selected << action->text();
        }
    }
    return selected;
}

void MultiSelectionBox::sl_UpdateText() {
    QStringList selected = SelectedItemNames();
    setEditText(selected.join(", "));
}