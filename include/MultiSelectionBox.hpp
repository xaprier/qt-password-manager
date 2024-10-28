#ifndef MULTISELECTIONBOX_HPP
#define MULTISELECTIONBOX_HPP

#include <qevent.h>

#include <QComboBox>
#include <QDebug>
#include <QLineEdit>
#include <QObject>

#include "MultiSelectionMenu.hpp"

class MultiSelectionBox : public QComboBox {
    Q_OBJECT

  public:
    MultiSelectionBox(QWidget *parent = nullptr);
    ~MultiSelectionBox() override;

    void AddItem(const QString &text, const QString &path);

    [[nodiscard]] QStringList SelectedItems() const;
    [[nodiscard]] QStringList SelectedItemNames() const;

  protected:
    void mousePressEvent(QMouseEvent *event) override {
        QComboBox::mousePressEvent(event);
        showPopup();  // internally call for every mouse press event
    }

    void showPopup() override {
        // Set the menu's width to match the line edit's width
        m_menu->setMinimumWidth(lineEdit()->width());
        QPoint pos = mapToGlobal(QPoint(0, height()));
        m_menu->exec(pos);
    }

  private slots:
    void sl_UpdateText();

  private:
    MultiSelectionMenu *m_menu;
};

#endif  // MULTISELECTIONBOX_HPP