#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include <visage_file_embed/embedded_file.h>

namespace gwr::gkqz
{

class DbManager
{
  public:
    SQLite::Database db;
    DbManager(std::string dbFileName);
    SQLite::Statement getStmt(std::string s);
    void secondHalf();
    const char *dbschema = R"foo(
CREATE TABLE morphs(
id INTEGER PRIMARY KEY AUTOINCREMENT,
inflected TEXT,
head TEXT,
parse TEXT,
lesson INTEGER
);

 )foo";

};

} // namespace gwr::gkqz
