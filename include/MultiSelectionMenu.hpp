#ifndef MULTISELECTIONMENU_HPP
#define MULTISELECTIONMENU_HPP

#include <QAction>
#include <QEvent>
#include <QMenu>
#include <QMouseEvent>

class MultiSelectionMenu : public QMenu {
    Q_OBJECT

  public:
    MultiSelectionMenu(QWidget *parent = nullptr) : QMenu(parent) {
        installEventFilter(this);
    }

  protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif  // MULTISELECTIONMENU_HPP