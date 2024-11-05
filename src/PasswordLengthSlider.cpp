#include "PasswordLengthSlider.hpp"

#include <QDebug>

void PasswordLengthSlider::mousePressEvent(QMouseEvent *event) {
    Qt::MouseButtons btns = QApplication::mouseButtons();
    QPoint localMousePos = mapFromGlobal(QCursor::pos());
    bool clickOnSlider = (btns & Qt::LeftButton) &&
                         (localMousePos.x() >= 0 && localMousePos.y() >= 0 &&
                          localMousePos.x() < size().width() &&
                          localMousePos.y() < size().height());

    if (clickOnSlider) {
        this->m_Clicked = clickOnSlider;
        float posRatio = localMousePos.x() / static_cast<float>(size().width());
        int sliderRange = maximum() - minimum();
        int sliderPosUnderMouse = minimum() + sliderRange * posRatio;

        if (sliderPosUnderMouse != value()) {
            setValue(sliderPosUnderMouse);
            return;
        }
    }

    QSlider::mousePressEvent(event);
}

void PasswordLengthSlider::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && m_Clicked) {
        this->m_Clicked = false;
        event->accept();
    } else {
        QSlider::mouseReleaseEvent(event);
    }
}

void PasswordLengthSlider::mouseMoveEvent(QMouseEvent *event) {
    if (this->m_Clicked) {
        float posRatio = event->pos().x() / static_cast<float>(width());
        int sliderRange = maximum() - minimum();
        int sliderPosUnderMouse = minimum() + sliderRange * posRatio;
        setValue(sliderPosUnderMouse);
        event->accept();
    } else {
        QSlider::mouseMoveEvent(event);
    }
}