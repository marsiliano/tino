#include "../gui/MainWindow.hpp"

#include <QApplication>
#include <QDebug>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    std::vector<bool> v = {
        true, false, true, false, true, false, true, false
    };
    std::vector<std::string> s = {
        "bitname1", "bitname2", "bitname3", "bitname4",
        "bitname5", "bitname6", "bitname7", "bitname8",
    };
    std::vector<std::string> s1 = { "bytename" };

    core::Byte b(v, s, true);
    core::Byte b1 = b;

    if (b == b1)
        qDebug() << "works";
    else
        qDebug() << "doesn't work";

    return a.exec();
}
