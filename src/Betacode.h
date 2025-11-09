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

#include <string>

extern "C"
{
    // found in unibetacode lib
    int ub_beta2greek(char *beta, int max_beta, char *utf8gk, int max_utf8);
    int ub_greek2beta(char *, int, char *, int);
}

struct Betacode
{
  public:
    std::string beta{"lo/gos"};
    static std::string beta2greek(const std::string &utf8);
    static std::string greek2beta(const std::string &greek);
};