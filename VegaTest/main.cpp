#include <QApplication>

#include "CoreApp.h"

int main(int argc, char *argv[])
{
    CoreApp app(argc, argv);

    if (!app.init())
        return 0;

    const int appError = app.exec();

    return appError;
}
