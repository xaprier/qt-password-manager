#include "PasswordLengthSlider.hpp"

void PasswordLengthSlider::mousePressEvent(QMouseEvent *event) {
    Qt::MouseButtons btns = QApplication::mouseButtons();
    QPoint localMousePos = mapFromGlobal(QCursor::pos());
    bool clickOnSlider = (btns & Qt::LeftButton) &&
                         (localMousePos.x() >= 0 && localMousePos.y() >= 0 &&
                          localMousePos.x() < size().width() &&
                          localMousePos.y() < size().height());

    if (clickOnSlider) {
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