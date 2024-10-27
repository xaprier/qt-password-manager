#include "MultiSelectionBox.hpp"

#include "MultiSelectionMenu.hpp"

MultiSelectionBox::MultiSelectionBox(QWidget *parent) : QComboBox(parent), menu(new MultiSelectionMenu(this)) {
    setEditable(true);
    lineEdit()->setReadOnly(true);
}

MultiSelectionBox::~MultiSelectionBox() {
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