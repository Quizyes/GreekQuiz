#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include <visage_file_embed/embedded_file.h>
#include "embedded/mydbs.h"
#include <sqlite3.h>

namespace gwr::gkqz
{

class DbManager
{
  public:
    SQLite::Database db;
    DbManager(std::string dbFileName);
    SQLite::Statement getStmt(std::string s);
};

} // namespace gwr::gkqz
