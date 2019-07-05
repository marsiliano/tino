#include <../widget/Mask.hpp>
#include <MainWindow.hpp>
#include <QApplication>
#include <QDebug>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //    std::vector<Mask> vm;

    //    std::vector<bool> v1 = {
    //        true, false, true, false, true, false, true, false
    //    };
    //    std::vector<std::string> s = { "prova" };
    //    core::Byte b2(v, s, false);
    //    Mask m1(b, nullptr);

    //    std::vector<bool> v2 = {
    //        true, false, true, false, true, false, true, false
    //    };
    //    std::vector<std::string> s = { "prova" };
    //    core::Byte b2(v, s, false);
    return a.exec();
}
