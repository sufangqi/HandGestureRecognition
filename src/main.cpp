#include "hanggusturecontrol.h"
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/new/prefix1/8403963.jpg");
    QSplashScreen screen(pixmap);
    screen.show();
    HangGustureControl w;
    w.show();
    screen.finish(&w);
    w.show();

    return a.exec();
}
