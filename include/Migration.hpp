#ifndef MIGRATIONOLDDATATONEW_HPP
#define MIGRATIONOLDDATATONEW_HPP

#include "MigrationException.hpp"

class Migration {
  public:
    virtual void Migrate() = 0;
};

#endif  // MIGRATIONOLDDATATONEW_HPP