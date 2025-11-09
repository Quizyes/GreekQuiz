////////////////////////////////////////////////////////////////////////// 
//                                                                      // 
// Greek Quiz - a suite of apps for practicing Ancient Greek.           // 
//                                                                      // 
// Copyright 2025, Greg Recco                                           // 
//                                                                      // 
// Greek Quiz is released under the GNU General Public Licence v3       // 
// or later (GPL-3.0-or-later). The license is found in the 'LICENSE'   // 
// file in the root of this repository, or at                           // 
// https://www.gnu.org/licenses/gpl-3.0.en.html                         // 
//                                                                      // 
// The source code repository for Greek Quiz is available at            // 
// https://github.com/Quizyes/GreekQuiz                                 // 
//                                                                      // 
////////////////////////////////////////////////////////////////////////// 

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
