#ifndef ENCFILELISTLOADER_HPP
#define ENCFILELISTLOADER_HPP

#include <QComboBox>
#include <QDir>
#include <QFileInfoList>
#include <QStandardPaths>
#include <QString>

class EncFileListLoader {
  public:
    EncFileListLoader(QComboBox* comboBox);
    void LoadEncFiles();

  private:
    QComboBox* m_comboBox;
};

#endif  // ENCFILELISTLOADER_HPP