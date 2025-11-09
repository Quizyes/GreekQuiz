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

#include "DbManager.h"

namespace gwr::gkqz
{

SQLite::Statement DbManager::getStmt(std::string s) { return SQLite::Statement{db, s}; }

DbManager::DbManager(std::string dbFilename)
    : db(dbFilename, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    int rv = sqlite3_deserialize(
        db.getHandle(), "main", (unsigned char *)resources::dbs::gkqz_db.data,
        resources::dbs::gkqz_db.size, resources::dbs::gkqz_db.size, SQLITE_DESERIALIZE_RESIZEABLE);
}

} // namespace gwr::gkqz