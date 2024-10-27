#include "MultiSelectionBox.hpp"

#include "MultiSelectionMenu.hpp"

MultiSelectionBox::MultiSelectionBox(QWidget *parent) : QComboBox(parent), m_menu(new MultiSelectionMenu(this)) {
    setEditable(true);
    lineEdit()->setReadOnly(true);
}

MultiSelectionBox::~MultiSelectionBox() {
}

void MultiSelectionBox::AddItem(const QString &text) {
    auto *action = new QAction(text, this);
    action->setCheckable(true);
    connect(action, &QAction::toggled, this, &MultiSelectionBox::sl_UpdateText);
    m_menu->addAction(action);
}

QStringList MultiSelectionBox::SelectedItems() const {
    QStringList selected;
    for (QAction *action : m_menu->actions()) {
        if (action->isChecked()) {
            selected << action->text();
        }
    }
    return selected;
}

void MultiSelectionBox::sl_UpdateText() {
    QStringList selected = SelectedItems();
    setEditText(selected.join(", "));
}