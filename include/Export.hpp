#ifndef EXPORT_HPP
#define EXPORT_HPP

#include <qglobal.h>
#include <qobject.h>
#include <qobjectdefs.h>

/**
 * @brief This class should create an dialog to select which file will exports with multiple selection.
 *        then create file dialog with directory selection
 *        and selected files will be copied to the correct directory
 *
 */
class Export : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(Export)
  public:
    explicit Export(QObject *base = nullptr);

  private:
};

#endif  // EXPORT_HPP