#ifndef CONFIGMANAGER_HPP
#define CONFIGMANAGER_HPP

#include <QSettings>

#include "DataDirs.hpp"
#include "Defines.hpp"
#include "singleton.hpp"

class ConfigManager : public QObject {
    Q_DISABLE_COPY_MOVE(ConfigManager)
  public:
    friend class Singleton<ConfigManager>;

    void SaveDataDirs(const DataDirs& dataDirs) {
        m_Settings.beginGroup("DataDirs");
        m_Settings.remove("");  // Clear existing keys
        m_Settings.beginWriteArray("Dirs");
        for (int i = 0; i < dataDirs.GetDataDirs().size(); ++i) {
            m_Settings.setArrayIndex(i);
            m_Settings.setValue("Path", dataDirs.GetDataDirs()[i].GetPath());
        }
        m_Settings.endArray();
        m_Settings.endGroup();
    }

    void LoadDataDirs(DataDirs& dataDirs) {
        m_Settings.beginGroup("DataDirs");
        int size = m_Settings.beginReadArray("Dirs");
        dataDirs.ClearDataDirs();
        for (int i = 0; i < size; ++i) {
            m_Settings.setArrayIndex(i);
            QString path = m_Settings.value("Path").toString();
            dataDirs.AddDataDir(DataDir(path));
        }
        m_Settings.endArray();
        m_Settings.endGroup();
    }

  private:
    ConfigManager() : m_Settings(ORGNAME, APPNAME) {}
    ~ConfigManager() = default;

  private:
    static ConfigManager& m_Manager;
    QSettings m_Settings;
};

#endif  // CONFIGMANAGER_HPP