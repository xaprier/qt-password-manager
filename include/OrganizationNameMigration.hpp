#ifndef ORGANIZATIONNAMEMIGRATION_HPP
#define ORGANIZATIONNAMEMIGRATION_HPP

#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QStandardPaths>

#include "Defines.hpp"
#include "Logger.hpp"
#include "Migration.hpp"
/**
 * @brief Migration class will migrate old organization name 'xaprier' to new organization name 'SFENX'
 * it will check there is encrypted files in old appdata directory. if there is, it will ask to copy files
 * and delete old directory from system.
 */
class OrganizationNameMigration : public Migration {
  public:
    OrganizationNameMigration() {
        Migrate();
    }

    virtual void Migrate() override;
};

#endif  // ORGANIZATIONNAMEMIGRATION_HPP