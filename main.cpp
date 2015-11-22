#include "maindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainDialog w;
    w.setWindowTitle("QR Code Generator");

    w.show();
    
    return a.exec();
}
