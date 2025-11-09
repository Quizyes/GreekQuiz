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

#include <visage_app/application_window.h>
#include <visage_file_embed/embedded_file.h>
#include "embedded/example_fonts.h"
#include "App.h"

int main()
{
    gwr::gkqz::App app;
    app.show(1200, 900);
    app.runEventLoop();
    return 0;
}
