#ifndef PASSWORDLENGTHSLIDER_HPP
#define PASSWORDLENGTHSLIDER_HPP

#include <QApplication>
#include <QMouseEvent>
#include <QSlider>
#include <QStyle>

class PasswordLengthSlider : public QSlider {
    Q_OBJECT

  public:
    PasswordLengthSlider(QWidget *parent = nullptr) : QSlider(parent) {}
    PasswordLengthSlider(Qt::Orientation orientation, QWidget *parent = nullptr)
        : QSlider(orientation, parent) {}

  protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif  // PASSWORDLENGTHSLIDER_HPP