#include "MultiSelectionBox.hpp"

MultiSelectionBox::MultiSelectionBox(QWidget *parent) : QComboBox(parent) {
    setEditable(true);
    lineEdit()->setReadOnly(true);

    // Custom menu for multiple selection
    menu = new MultiSelectionMenu(this);
}

MultiSelectionBox::~MultiSelectionBox() {
    delete menu;
}

void MultiSelectionBox::addItem(const QString &text) {
    auto *action = new QAction(text, this);
    action->setCheckable(true);
    connect(action, &QAction::toggled, this, &MultiSelectionBox::updateText);
    menu->addAction(action);
}

QStringList MultiSelectionBox::selectedItems() const {
    QStringList selected;
    for (QAction *action : menu->actions()) {
        if (action->isChecked()) {
            selected << action->text();
        }
    }
    return selected;
}

void MultiSelectionBox::updateText() {
    QStringList selected = selectedItems();
    setEditText(selected.join(", "));
}