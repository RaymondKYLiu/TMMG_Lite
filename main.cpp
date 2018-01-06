#include "mainwindow.h"
#include <QApplication>
#include "defines.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(w.windowTitle() + " ver. " + TMMG_VERSION
#ifdef TEST_ON_MY_FORM
                     + QStringLiteral(" 測試版")
#endif
                     );
    w.show();
    w.setStyleSheet("QLineEdit:focus { border: 2px solid #006080; background-color: lightblue }");
    return a.exec();
}
