#include "application.h"

int main(int argc, char *argv[])
{
    Application *app = new Application(argc, argv, QStringLiteral("Slate"));
    if (app->qmlEngine()->rootObjects().isEmpty())
        return 1;

#ifndef Q_OS_WASM
     app->run();
#endif

    return 0;
}
