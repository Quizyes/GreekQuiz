#include <visage_app/application_window.h>
#include <visage_file_embed/embedded_file.h>
#include "embedded/example_fonts.h"
#include "App.h"

int main()
{
    gwr::gkqz::App app;
    app.show(900, 675);
    app.runEventLoop();
    return 0;
}
