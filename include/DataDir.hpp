#ifndef DATADIR_HPP
#define DATADIR_HPP

#include "Dir.hpp"
#include "Logger.hpp"
#include "LoggingLevel.hpp"

class DataDir : public Dir {
  public:
    explicit DataDir(const QString& path = "") {
        QDir dir(path);
        if (!dir.exists(path)) {
            Logger::log_static(LoggingLevel::WARNING, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Invalid or not exists path: %1").arg(path).toStdString());
            return;
        }
        m_dir = dir;
    }

    QString GetPath() const override {
        return m_dir.absolutePath();
    }

    void SetPath(const QString& path) override {
        if (!m_dir.exists(path)) {
            Logger::log_static(LoggingLevel::WARNING, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Invalid or not exists path: %1").arg(path).toStdString());
            return;
        }
        m_dir.setPath(path);
    }

  private:
    QDir m_dir;
};

#endif  // DATADIR_HPP