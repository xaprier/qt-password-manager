#ifndef MULTISELECTIONBOX_HPP
#define MULTISELECTIONBOX_HPP

#include <QComboBox>
#include <QLineEdit>
#include <QObject>

#include "MultiSelectionMenu.hpp"

class MultiSelectionBox : public QComboBox {
    Q_OBJECT

  public:
    MultiSelectionBox(QWidget *parent = nullptr);
    ~MultiSelectionBox() override;

    void addItem(const QString &text);

    [[nodiscard]] QStringList selectedItems() const;

  protected:
    void showPopup() override {
        // Set the menu's width to match the line edit's width
        menu->setMinimumWidth(lineEdit()->width());
        QPoint pos = mapToGlobal(QPoint(0, height()));
        menu->exec(pos);
    }

  private slots:
    void updateText();

  private:
    MultiSelectionMenu *menu;
};

#endif  // MULTISELECTIONBOX_HPP