#include "MultiSelectionMenu.hpp"

bool MultiSelectionMenu::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        QWidget *clickedWidget = childAt(mouseEvent->pos());
        if (clickedWidget && clickedWidget->inherits("QAction")) {
            return true;  // Prevent the menu from closing
        }
    }
    return QMenu::eventFilter(obj, event);
}

void MultiSelectionMenu::mouseReleaseEvent(QMouseEvent *event) {
    QAction *action = actionAt(event->pos());
    if (action && action->isCheckable()) {
        action->toggle();
        return;  // Don't call the base class implementation
    }
    QMenu::mouseReleaseEvent(event);
}