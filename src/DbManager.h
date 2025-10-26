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
    void part1();
    void part2();
    void part3();
    void part4();
    void part5();
    void part6();
    void part7();
    void part8();
    void part9();
    void part10();
    void part11();
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
