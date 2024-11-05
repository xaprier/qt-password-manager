#ifndef CONFIGMANAGER_HPP
#define CONFIGMANAGER_HPP

#include <QSettings>

#include "Config.hpp"
#include "DataDirs.hpp"
#include "singleton.hpp"

class ConfigManager : public QObject {
    Q_DISABLE_COPY_MOVE(ConfigManager)
  public:
    friend class Singleton<ConfigManager>;

    void SaveDataDirs(const DataDirs& dataDirs) {
        m_settings.beginGroup("DataDirs");
        m_settings.remove("");  // Clear existing keys
        m_settings.beginWriteArray("Dirs");
        for (int i = 0; i < dataDirs.GetDataDirs().size(); ++i) {
            m_settings.setArrayIndex(i);
            m_settings.setValue("Path", dataDirs.GetDataDirs()[i].GetPath());
        }
        m_settings.endArray();
        m_settings.endGroup();
    }

    void LoadDataDirs(DataDirs& dataDirs) {
        m_settings.beginGroup("DataDirs");
        int size = m_settings.beginReadArray("Dirs");
        dataDirs.ClearDataDirs();
        for (int i = 0; i < size; ++i) {
            m_settings.setArrayIndex(i);
            QString path = m_settings.value("Path").toString();
            dataDirs.AddDataDir(DataDir(path));
        }
        m_settings.endArray();
        m_settings.endGroup();
    }

  private:
    ConfigManager() : m_settings(PROJECT_ORGANIZATION, PROJECT_NAME) {}
    ~ConfigManager() = default;

  private:
    static ConfigManager& m_manager;
    QSettings m_settings;
};

#endif  // CONFIGMANAGER_HPP