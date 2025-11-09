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

#include "Betacode.h"
#include <cstring>

std::string Betacode::beta2greek(const std::string &beta)
{
    char cstr[150]{0};
    strncpy(cstr, beta.c_str(), beta.length());
    char gkstr[150]{0};
    ub_beta2greek(cstr, 150, gkstr, 150);
    return std::string(gkstr);
}
std::string Betacode::greek2beta(const std::string &greek)
{
    char gkstr[150]{0};
    strncpy(gkstr, greek.c_str(), greek.length());
    char cstr[150]{0};
    ub_beta2greek(cstr, 150, gkstr, 150);
    return std::string(cstr);
}
