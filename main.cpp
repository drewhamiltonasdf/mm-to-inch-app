#include "mm_to_inch_app.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mm_to_inch_app w;

    QFile StyleFile(":/Combinear/Combinear.qss");
    StyleFile.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(StyleFile.readAll());
    w.setStyleSheet(StyleSheet);

    w.show();
    return a.exec();
}
