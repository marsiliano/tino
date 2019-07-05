#include <MainWindow.hpp>
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
    std::vector<std::string> s = { "prova" };
    core::Byte b(v, s, false);
    Mask m(b, nullptr);

    m.show();

    return a.exec();
}
