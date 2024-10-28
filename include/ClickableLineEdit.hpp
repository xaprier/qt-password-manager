#ifndef CLICKABLELINEEDIT_HPP
#define CLICKABLELINEEDIT_HPP

#include <QLineEdit>
#include <QWidget>

class ClickableLineEdit : public QLineEdit {
    Q_OBJECT

  public:
    explicit ClickableLineEdit(QWidget *parent = nullptr) : QLineEdit(parent) {}

  signals:
    void clicked();

  protected:
    void mousePressEvent(QMouseEvent *event) override {
        emit clicked();
        QLineEdit::mousePressEvent(event);
    }
};

#endif  // CLICKABLELINEEDIT_HPP