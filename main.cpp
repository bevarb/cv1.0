#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//添加qss,用来设计样式
    QString qss;
    QFile qssFile(":/style/style.qss");
    qssFile.open(QFile::ReadOnly);
    if (qssFile.isOpen())
    {

        qss = QLatin1String(qssFile.readAll());

        a.setStyleSheet(qss);
        qApp->setStyleSheet(qss);
        qssFile.close();
    }


    MainWindow w;
    w.show();

    return a.exec();
}
