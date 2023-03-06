#include "application.h"

int main(int argc, char *argv[])
{
    Application *app = new Application(argc, argv, QStringLiteral("Slate"));
    if (app->qmlEngine()->rootObjects().isEmpty())
        return 1;
    return 0;
}
